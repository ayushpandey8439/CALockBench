//
// Created by Ayush Pandey on 15/07/2024.
//

#ifndef INTENTION_LOCK_SRV_H
#define INTENTION_LOCK_SRV_H
#include <stack>

#include "../../struct/design_obj.h"
#include <map>
#include <mutex>
#include <queue>
#include <set>

#include "../../data_holder.h"
#include "../../struct/atomic_part.h"
#include "../../struct/composite_part.h"
#include "../../struct/connection.h"

//TODO: Convert this to a blocking intention lock  implementation instead of busy waiting i.e. When threads are waiting for a lock,
// they should block on an atomic conditional instead of checking what the intention level is.

using namespace sb7;

class Intention_lock_srv
{


public:
    std::chrono::duration<long double, std::nano> idleness[512];
    static void ISLock(int tid, DesignObj* obj)
    {
    check:
        while (obj->intentionLevel == 4 && !obj->lockers.contains(tid))
        {
        }

        Lock(&obj->NodeMutex);
        if (obj->intentionLevel != 4)
        {
            pthread_rwlock_rdlock(&obj->NodeLock);
            if (obj->intentionLevel < 1)
                obj->intentionLevel = 1;
            obj->refCounter++;
        }
        else
        {
            Unlock(&obj->NodeMutex);
            goto check;
        }
        Unlock(&obj->NodeMutex);
    }

    static void IXLock(int tid, DesignObj* obj)
    {
    check:
        while (obj->intentionLevel > 2 && !obj->lockers.contains(tid))
        {
        }

        Lock(&obj->NodeMutex);
        if (obj->intentionLevel <= 2)
        {
            pthread_rwlock_rdlock(&obj->NodeLock);
            if (obj->intentionLevel < 2)
                obj->intentionLevel = 2;
            obj->refCounter++;
        }
        else
        {
            Unlock(&obj->NodeMutex);
            goto check;
        }
        Unlock(&obj->NodeMutex);
    }

    static void SLock(int tid, DesignObj* obj)
    {
    check:
        while ((obj->intentionLevel == 2 || obj->intentionLevel == 4) && !obj->lockers.contains(tid))
        {
        }

        Lock(&obj->NodeMutex);
        if (obj->intentionLevel != 2 && obj->intentionLevel != 4)
        {
            pthread_rwlock_rdlock(&obj->NodeLock);
            if (obj->intentionLevel < 3)
                obj->intentionLevel = 3;
            obj->refCounter++;
        }
        else
        {
            Unlock(&obj->NodeMutex);
            goto check;
        }
        Unlock(&obj->NodeMutex);
    }

    static void XLock(int tid, DesignObj* obj)
    {
    check:
        while (obj->refCounter != 0 && !obj->lockers.contains(tid))
        {
        }

        Lock(&obj->NodeMutex);
        if (obj->refCounter == 0)
        {
            pthread_rwlock_wrlock(&obj->NodeLock);
            obj->intentionLevel = 4;
            obj->refCounter++;
        }
        else
        {
            Unlock(&obj->NodeMutex);
            goto check;
        }
        Unlock(&obj->NodeMutex);
    }

    static void IUnlock(int tid, DesignObj* obj)
    {
        Lock(&obj->NodeMutex);
        pthread_rwlock_unlock(&obj->NodeLock);
        obj->refCounter--;
        obj->lockers.erase(tid);
        if(obj->lockers.empty())
            obj->intentionLevel=0;

        Unlock(&obj->NodeMutex);
    }

    static void Lock(pthread_mutex_t* objLock)
    {
        pthread_mutex_lock(objLock);
    }

    static void Unlock(pthread_mutex_t* objLock)
    {
        pthread_mutex_unlock(objLock);
    }

    void getLockStack(AtomicPart* atomicPart, set<int>* visited = new set<int>())
    {
        if (visited->contains((atomicPart->getId() * 10) + 4)) return;

        visited->insert((atomicPart->getId() * 10) + 4);
        auto cpart = atomicPart->getPartOf();
        if (cpart != nullptr)
            getLockStack(cpart, visited);
    }

    void getLockStack(CompositePart* cpart, set<int>* visited = new set<int>())
    {
        if (visited->contains((cpart->getId() * 10) + 3)) return;

        visited->insert((cpart->getId() * 10) + 3);
        auto bassms = cpart->getUsedIn();
        auto iter = bassms->getIter();
        while (iter.has_next())
        {
            auto bassm = iter.next();
            getLockStack(bassm, visited);
        }
    }

    void getLockStack(BaseAssembly* bassm, set<int>* visited = new set<int>())
    {
        if (visited->contains((bassm->getId() * 10) + 2)) return;
        visited->insert((bassm->getId() * 10) + 2);
        auto cassm = bassm->getSuperAssembly();
        if (cassm != nullptr)
            getLockStack(cassm, visited);
    }


    void getLockStack(ComplexAssembly* cassm, set<int>* visited = new set<int>())
    {
        if (visited->contains((cassm->getId() * 10) + 1)) return;

        visited->insert((cassm->getId() * 10) + 1);
        auto superAssembly = cassm->getSuperAssembly();
        if (superAssembly != nullptr)
            getLockStack(superAssembly, visited);
    }

    void IntentionLock(int tid, DataHolder* dh, DesignObj* target, const int mode, set<int>* toLock)
    {
        auto t1 = std::chrono::high_resolution_clock::now();
        queue<ComplexAssembly*> cassmsQ;
        queue<BaseAssembly*> bassmsQ;
        queue<CompositePart*> cpartsQ;
        queue<AtomicPart*> apartsQ;
        cassmsQ.push(dh->getModule()->getDesignRoot());

        while (!cassmsQ.empty())
        {
            auto cassm = cassmsQ.front();
            if (toLock->contains((cassm->getId() * 10) + 1))
            {
                IntentionLock(tid, cassm, target, mode, &cassmsQ, &bassmsQ);
            }
            cassmsQ.pop();
        }
        while (!bassmsQ.empty())
        {
            auto bassm = bassmsQ.front();
            if (toLock->contains((bassm->getId() * 10) + 2))
            {
                IntentionLock(tid, bassm, target, mode, cpartsQ);
            }
            bassmsQ.pop();
        }
        while (!cpartsQ.empty())
        {
            auto cpart = cpartsQ.front();
            if (toLock->contains((cpart->getId() * 10) + 3))
            {
                IntentionLock(tid, cpart, target, mode, apartsQ);
            }
            cpartsQ.pop();
        }
        while (!apartsQ.empty())
        {
            auto apart = apartsQ.front();
            if (toLock->contains((apart->getId() * 10) + 4))
            {
                IntentionLock(tid, apart, target, mode, apartsQ);
            }
            apartsQ.pop();
        }
        auto t2 = std::chrono::high_resolution_clock::now();
        idleness[tid] += (t2 - t1);
    }


    void IntentionLock(int tid, ComplexAssembly* cassm, DesignObj* target, const int mode,
                       queue<ComplexAssembly*>* cassmsQ,
                       queue<BaseAssembly*>* bassmsQ)
    {
        if ((DesignObj*)cassm == target)
        {
            mode == 0 ? SLock(tid, target) : XLock(tid, target);
        }
        else
        {
            mode == 0 ? ISLock(tid, cassm) : IXLock(tid, cassm);
            auto subassemblies = cassm->getSubAssemblies();
            auto iter = subassemblies->getIter();
            bool areChildrenBase = cassm->areChildrenBaseAssemblies();

            while (iter.has_next())
            {
                if (areChildrenBase)
                    bassmsQ->push((BaseAssembly*)iter.next());
                else
                    cassmsQ->push((ComplexAssembly*)iter.next());
            }
        }
    }

    void IntentionLock(int tid, BaseAssembly* bassm, DesignObj* target, int mode, queue<CompositePart*> cpartQ)
    {
        if ((DesignObj*)bassm == target)
        {
            mode == 0 ? SLock(tid, target) : XLock(tid, target);
        }
        else
        {
            mode == 0 ? ISLock(tid, bassm) : IXLock(tid, bassm);

            auto components = bassm->getComponents();
            auto iter = components->getIter();
            while (iter.has_next())
            {
                cpartQ.push(iter.next());
            }
        }
    }

    void IntentionLock(int tid, CompositePart* cpart, DesignObj* target, int mode, queue<AtomicPart*> apartsQ)
    {
        if ((DesignObj*)cpart == target)
        {
            mode == 0 ? SLock(tid, target) : XLock(tid, target);
        }
        else
        {
            mode == 0 ? ISLock(tid, cpart) : IXLock(tid, cpart);
            apartsQ.push(cpart->getRootPart());
            // mode ==0? SLock(target): XLock(target);
            // AtomicPart* rootPart = cpart->getRootPart();
            // IntentionLock(rootPart, target, mode, toLock, locked);
        }
    }

    void IntentionLock(int tid, AtomicPart* apart, DesignObj* target, int mode, queue<AtomicPart*> apartsQ)
    {
        if ((DesignObj*)apart == target)
        {
            mode == 0 ? SLock(tid, target) : XLock(tid, target);
        }
        else
        {
            mode == 0 ? ISLock(tid, apart) : IXLock(tid, apart);
            auto conns = apart->getToConnections();
            auto iter = conns->getIter();
            while (iter.has_next())
            {
                apartsQ.push(iter.next()->getDestination());
            }
        }
    }


    void IntentionUnlock(int tid, AtomicPart* atomicPart, set<int>* locksRequired, set<int>* unlocked = new set<int>())
    {
        if (!locksRequired->contains((atomicPart->getId() * 10) + 4) || unlocked->contains(
            (atomicPart->getId() * 10) + 4))
            return;
        IUnlock(tid, atomicPart);
        unlocked->insert((atomicPart->getId() * 10) + 4);


        auto cpart = atomicPart->getPartOf();
        if (cpart != nullptr)
            IntentionUnlock(tid, cpart, locksRequired);
    }

    void IntentionUnlock(int tid, CompositePart* cpart, set<int>* locksRequired, set<int>* unlocked = new set<int>())
    {
        if (!locksRequired->contains((cpart->getId() * 10) + 3) || unlocked->contains((cpart->getId() * 10) + 3))
            return;
        IUnlock(tid, cpart);
        unlocked->insert((cpart->getId() * 10) + 3);

        auto bassms = cpart->getUsedIn();
        auto iter = bassms->getIter();
        while (iter.has_next())
        {
            auto bassm = iter.next();
            IntentionUnlock(tid, bassm, locksRequired, unlocked);
        }
    }

    void IntentionUnlock(int tid, BaseAssembly* bassm, set<int>* locksRequired, set<int>* unlocked = new set<int>())
    {
        if (!locksRequired->contains((bassm->getId() * 10) + 2) || unlocked->contains((bassm->getId() * 10) + 2))
            return;
        IUnlock(tid, bassm);
        unlocked->insert((bassm->getId() * 10) + 2);
        auto cassm = bassm->getSuperAssembly();
        if (cassm != nullptr)
            IntentionUnlock(tid, cassm, locksRequired, unlocked);
    }


    void IntentionUnlock(int tid, ComplexAssembly* cassm, set<int>* locksRequired, set<int>* unlocked = new set<int>())
    {
        if (!locksRequired->contains((cassm->getId() * 10) + 1) || unlocked->contains((cassm->getId() * 10) + 1))
            return;
        IUnlock(tid, cassm);
        unlocked->insert((cassm->getId() * 10) + 1);

        auto superAssembly = cassm->getSuperAssembly();
        if (superAssembly != nullptr)
            IntentionUnlock(tid, superAssembly, locksRequired, unlocked);
    }
};


#endif //INTENTION_LOCK_SRV_H
