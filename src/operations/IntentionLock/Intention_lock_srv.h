#ifndef INTENTION_LOCK_SRV_H
#define INTENTION_LOCK_SRV_H
#include <stack>

#include "../../struct/design_obj.h"
#include <map>
#include <mutex>
#include <queue>
#include <set>
#include <algorithm>
#include <exception>
#include <functional>
#include <variant>

#include "../../data_holder.h"
#include "../../struct/atomic_part.h"
#include "../../struct/composite_part.h"
#include "../../sb7_exception.h"
#include "../../thread/thread.h"

//TODO: Convert this to a blocking intention lock  implementation instead of busy waiting i.e. When threads are waiting for a lock,
// they should block on an atomic conditional instead of checking what the intention level is.

using namespace sb7;

class Intention_lock_srv
{
public:
    std::chrono::duration<long double, std::nano> idleness[512]{};
    int lockRejection[512]{};

    Intention_lock_srv()
    {
        for (auto& i : idleness)
        {
            i = std::chrono::duration<long double, std::nano>(0);
        }
        for (auto& i : lockRejection)
        {
            i = 0;
        }
    }

    void getLockStack(const AtomicPart* atomicPart, set<int>* visited = new set<int>())
    {
        if (visited->contains((atomicPart->getId() * 10) + 4)) return;

        visited->insert((atomicPart->getId() * 10) + 4);
        if (const auto cpart = atomicPart->getPartOf(); cpart != nullptr)
            getLockStack(cpart, visited);
    }

    void getLockStack(const CompositePart* cpart, set<int>* visited = new set<int>())
    {
        if (visited->contains((cpart->getId() * 10) + 3)) return;
        visited->insert((cpart->getId() * 10) + 3);
        const auto bassms = cpart->getUsedIn();
        auto iter = bassms->getIter();
        while (iter.has_next())
        {
            const auto bassm = iter.next();
            getLockStack(bassm, visited);
        }
    }

    void getLockStack(const BaseAssembly* bassm, set<int>* visited = new set<int>())
    {
        if (visited->contains((bassm->getId() * 10) + 2)) return;
        visited->insert((bassm->getId() * 10) + 2);
        const auto cassm = bassm->getSuperAssembly();
        if (cassm != nullptr)
            getLockStack(cassm, visited);
    }


    void getLockStack(const ComplexAssembly* cassm, set<int>* visited = new set<int>())
    {
        if (visited->contains((cassm->getId() * 10) + 1)) return;

        visited->insert((cassm->getId() * 10) + 1);
        const auto superAssembly = cassm->getSuperAssembly();
        if (superAssembly != nullptr)
            getLockStack(superAssembly, visited);
    }

    void IntentionLock(const int tid, DataHolder* dh, const set<DesignObj*>* targets, const int type, const int mode,
                       const set<int>* lockStack)
    {
        int locksRejected = 0;
    retake:
        try
        {
            auto t1 = std::chrono::high_resolution_clock::now();
            queue<ComplexAssembly*> cassmsQ;
            queue<BaseAssembly*> bassmsQ;
            queue<CompositePart*> cpartsQ;
            queue<AtomicPart*> apartsQ;
            cassmsQ.push(dh->getModule()->getDesignRoot());
            set<int> visited;
            while (!cassmsQ.empty())
            {
                auto cassm = cassmsQ.front();
                if (lockStack->contains((cassm->getId() * 10) + 1))
                {
                    IntentionLock(tid, cassm, targets, type, mode, &cassmsQ, &bassmsQ, &visited);
                }
                cassmsQ.pop();
            }
            while (!bassmsQ.empty())
            {
                const auto bassm = bassmsQ.front();
                if (lockStack->contains((bassm->getId() * 10) + 2))
                {
                    IntentionLock(tid, bassm, targets, type, mode, &cpartsQ, &visited);
                }
                bassmsQ.pop();
            }

            while (!cpartsQ.empty())
            {
                const auto cpart = cpartsQ.front();
                if (lockStack->contains((cpart->getId() * 10) + 3))
                {
                    IntentionLock(tid, cpart, targets, type, mode, &apartsQ, &visited);
                }
                cpartsQ.pop();
            }

            while (!apartsQ.empty())
            {
                const auto apart = apartsQ.front();
                if (lockStack->contains((apart->getId() * 10) + 4))
                {
                    IntentionLock(tid, apart, type, mode, &visited);
                }
                apartsQ.pop();
            }


            auto t2 = std::chrono::high_resolution_clock::now();
            idleness[tid] += (t2 - t1);
            if (lockStack->size() != visited.size())
            {
                throw sb7::Sb7Exception();
            }
        }
        catch (runtime_error& e)
        {

            locksRejected++;
            sleep(10);
            if (locksRejected < 20)
            {
                goto retake;
            }
            lockRejection[tid]++;
            throw sb7::Sb7Exception();
        }
    }

    void IntentionLock(const int tid, ComplexAssembly* cassm, const set<DesignObj*>* targets, const int type,
                       const int mode,
                       queue<ComplexAssembly*>* cassmsQ, queue<BaseAssembly*>* bassmsQ,
                       set<int>* visited = new set<int>())
    {
        if (visited->contains(cassm->getId() * 10 + 1)) return;
        try
        {
            if (targets->contains(cassm))
            {
                mode == 0 ? SLock(tid, cassm) : XLock(tid, cassm);
            }
            else
            {
                mode == 0 ? ISLock(tid, cassm) : IXLock(tid, cassm);

                const auto subassemblies = cassm->getSubAssemblies();
                auto iter = subassemblies->getIter();
                const auto areChildrenBase = cassm->areChildrenBaseAssemblies();
                while (iter.has_next())
                {
                    if (areChildrenBase)
                        bassmsQ->push((BaseAssembly*)iter.next());
                    else
                        cassmsQ->push((ComplexAssembly*)iter.next());
                }
            }
            visited->insert((cassm->getId() * 10) + 1);
        }
        catch (exception_ptr e)
        {
            IntentionUnlock(tid, targets, type, visited);
            rethrow_exception(e);
        }
    }

    void IntentionLock(const int tid, BaseAssembly* bassm, const set<DesignObj*>* targets, const int type,
                       const int mode,
                       queue<CompositePart*>* cpartQ, set<int>* visited = new set<int>())
    {
        if (visited->contains(bassm->getId() * 10 + 2)) return;

        try
        {
            if (targets->contains(bassm))
            {
                mode == 0 ? SLock(tid, bassm) : XLock(tid, bassm);
            }
            else
            {
                mode == 0 ? ISLock(tid, bassm) : IXLock(tid, bassm);
                const auto components = bassm->getComponents();
                auto iter = components->getIter();
                while (iter.has_next())
                {
                    cpartQ->push(iter.next());
                }
            }
            visited->insert((bassm->getId() * 10) + 2);
        }
        catch (exception_ptr e)
        {
            IntentionUnlock(tid, targets, type, visited);
            rethrow_exception(e);
        }
    }

    void IntentionLock(const int tid, CompositePart* cpart, const set<DesignObj*>* targets, const int type,
                       const int mode,
                       queue<AtomicPart*>* apartsQ, set<int>* visited = new set<int>())
    {
        if (visited->contains(cpart->getId() * 10 + 3)) return;
        try
        {
            if (targets->contains(cpart))
            {
                mode == 0 ? SLock(tid, cpart) : XLock(tid, cpart);
            }
            else
            {
                mode == 0 ? ISLock(tid, cpart) : IXLock(tid, cpart);
                for (const auto apart : *targets)
                {
                    if (visited->contains(apart->getId() * 10 + 4)) continue;
                    visited->insert((apart->getId() * 10) + 4);
                    apartsQ->push((AtomicPart*)apart);
                }
            }
            visited->insert((cpart->getId() * 10) + 3);
        }
        catch (exception_ptr e)
        {
            IntentionUnlock(tid, targets, type, visited);
            rethrow_exception(e);
        }
    }

    void IntentionLock(const int tid, DesignObj* target, const int type, const int mode, set<int>* visited)
    {
        try
        {
            mode == 0 ? SLock(tid, target) : XLock(tid, target);
        }
        catch (exception_ptr e)
        {
            auto targets = set<DesignObj*>{target};
            IntentionUnlock(tid, &targets, 4, visited);
            rethrow_exception(e);
        }
    }

    bool ISLock(int tid, DesignObj* vertex)
    {
        unique_lock<mutex> lk(vertex->NodeMutex);

        vertex->intentionLocked.wait_for(lk, chrono::milliseconds(100), [vertex]
        {
            if (vertex->intentionLevel != 4) return true;
            throw runtime_error("IS Lock failed");
        });
        vertex->lockers.insert(pair(tid, 1));
        vertex->intentionLevel = ranges::max_element(vertex->lockers.begin(), vertex->lockers.end(),
                                                     [](const pair<int, int>& a, const pair<int, int>& b)
                                                     {
                                                         return a.second < b.second;
                                                     })->second;
        return true;
    }

    bool IXLock(int tid, DesignObj* vertex)
    {
        unique_lock<mutex> lk(vertex->NodeMutex);
        vertex->intentionLocked.wait_for(lk, chrono::milliseconds(100), [vertex]
        {
            if (vertex->intentionLevel <= 2)
            {
                return true;
            }
            throw runtime_error("IX Lock failed");
        });
        vertex->lockers.insert(pair(tid, 2));
        vertex->intentionLevel = ranges::max_element(vertex->lockers.begin(), vertex->lockers.end(),
                                                     [](const pair<int, int>& a, const pair<int, int>& b)
                                                     {
                                                         return a.second < b.second;
                                                     })->second;
        return true;
    }

    bool SLock(int tid, DesignObj* vertex)
    {
        unique_lock<mutex> lk(vertex->NodeMutex);
        bool failed = false;
        int count = 0;
        vertex->intentionLocked.wait_for(
            lk, chrono::milliseconds(100), [vertex]
            {
                if (vertex->intentionLevel != 2 && vertex->intentionLevel != 4) return true;
                throw runtime_error("S Lock failed");
            });

        vertex->lockers.insert(pair(tid, 3));
        vertex->intentionLevel = ranges::max_element(vertex->lockers.begin(), vertex->lockers.end(),
                                                     [](const pair<int, int>& a, const pair<int, int>& b)
                                                     {
                                                         return a.second < b.second;
                                                     })->second;
        return true;
    }

    bool XLock(const int tid, DesignObj* vertex)
    {
        unique_lock<mutex> lk(vertex->NodeMutex);
        vertex->intentionLocked.wait_for(lk, chrono::milliseconds(100), [vertex]
        {
            if (vertex->lockers.empty()) return true;
            throw runtime_error("X Lock failed");
        });
        vertex->lockers.insert(pair(tid, 4));
        vertex->intentionLevel = ranges::max_element(vertex->lockers.begin(), vertex->lockers.end(),
                                                     [](const pair<int, int>& a, const pair<int, int>& b)
                                                     {
                                                         return a.second < b.second;
                                                     })->second;
        return true;
    }

    void Unlock(int tid, DesignObj* vertex)
    {
        unique_lock<mutex> lk(vertex->NodeMutex);
        const auto it = ranges::find_if(vertex->lockers.begin(), vertex->lockers.end(),
                                        [tid](pair<int, int> a) { return a.first == tid; });
        if (it != vertex->lockers.end())
            vertex->lockers.erase(it);
        if (vertex->lockers.empty())
        {
            vertex->intentionLevel = 0;
        }
        else
        {
            vertex->intentionLevel = ranges::max_element(vertex->lockers.begin(), vertex->lockers.end(),
                                                         [](const pair<int, int>& a, const pair<int, int>& b)
                                                         {
                                                             return a.second < b.second;
                                                         })->second;
        }
        vertex->intentionLocked.notify_all();
    }


    void IntentionUnlock(int tid, const set<DesignObj*>* targets, const int type, set<int>* lockStack)
    {
        const auto t1 = std::chrono::high_resolution_clock::now();
        queue<ComplexAssembly*> cassmsQ;
        queue<BaseAssembly*> bassmsQ;
        queue<CompositePart*> cpartsQ;
        queue<AtomicPart*> apartsQ;
        switch (type)
        {
        case 1:
            for (const auto target : *targets)
                cassmsQ.push((ComplexAssembly*)target);
            break;
        case 2:
            for (const auto target : *targets)
                bassmsQ.push((BaseAssembly*)target);
            break;
        case 3:
            for (const auto target : *targets)
                cpartsQ.push((CompositePart*)target);
            break;
        case 4:
            for (const auto target : *targets)
                apartsQ.push((AtomicPart*)target);
        }

        while (!apartsQ.empty())
        {
            auto apart = apartsQ.front();
            if (lockStack->contains((apart->getId() * 10) + 4))
            {
                IntentionUnlock(tid, apart, &cpartsQ);
                lockStack->erase((apart->getId() * 10) + 4);
            }

            apartsQ.pop();
        }
        while (!cpartsQ.empty())
        {
            auto cpart = cpartsQ.front();
            if (lockStack->contains((cpart->getId() * 10) + 3))
            {
                IntentionUnlock(tid, cpart, &bassmsQ);
                lockStack->erase((cpart->getId() * 10) + 3);
            }

            cpartsQ.pop();
        }
        while (!bassmsQ.empty())
        {
            auto bassm = bassmsQ.front();
            if (lockStack->contains((bassm->getId() * 10) + 2))
            {
                IntentionUnlock(tid, bassm, &cassmsQ);
                lockStack->erase((bassm->getId() * 10) + 2);
            }

            bassmsQ.pop();
        }
        while (!cassmsQ.empty())
        {
            auto cassm = cassmsQ.front();
            if (lockStack->contains((cassm->getId() * 10) + 1))
            {
                IntentionUnlock(tid, cassm, &cassmsQ);
                lockStack->erase((cassm->getId() * 10) + 1);
            }

            cassmsQ.pop();
        }
        auto t2 = std::chrono::high_resolution_clock::now();
        idleness[tid] += (t2 - t1);
    }

    void IntentionUnlock(int tid, AtomicPart* apart, queue<CompositePart*>* cpartsQ)
    {
        Unlock(tid, apart);
        cpartsQ->push(apart->getPartOf());
    }

    void IntentionUnlock(int tid, CompositePart* cpart, queue<BaseAssembly*>* bassmsQ)
    {
        Unlock(tid, cpart);

        auto bassms = cpart->getUsedIn();
        auto iter = bassms->getIter();
        while (iter.has_next())
        {
            bassmsQ->push(iter.next());
        }
    }

    void IntentionUnlock(int tid, BaseAssembly* bassm, queue<ComplexAssembly*>* cassmsQ)
    {
        Unlock(tid, bassm);
        auto cassm = bassm->getSuperAssembly();
        if (cassm != nullptr)
            cassmsQ->push(cassm);
    }


    void IntentionUnlock(int tid, ComplexAssembly* cassm, queue<ComplexAssembly*>* cassmsQ)
    {
        Unlock(tid, cassm);
        auto superAssembly = cassm->getSuperAssembly();
        if (superAssembly != nullptr)
            cassmsQ->push(superAssembly);
    }
};


#endif //INTENTION_LOCK_SRV_H
