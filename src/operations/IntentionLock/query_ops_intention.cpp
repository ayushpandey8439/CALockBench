#include "query_ops_intention.h"

#include <stack>

#include "../../helpers.h"
#include "../../parameters.h"
#include "../../sb7_exception.h"
#include "./Intention_lock_srv.h"
#include <algorithm>
extern Intention_lock_srv ILSrv;
////////////
// Query1 //
////////////

#define QUERY1_ITER 10

int sb7::IntentionQuery1::run(int tid) const
{
    //ReadLockHandle readLockHandle(dom_lock_srv.getLock());
    return innerRun(tid);
}

int sb7::IntentionQuery1::innerRun(int tid) const
{
    int count = 0;
    int threadID = tid;
    long min = INTMAX_MAX, max = -1;
    int apartId = get_random()->nextInt(
        parameters.getMaxAtomicParts()) + 1;
    Map<int, AtomicPart*>* apartInd = dataHolder->getAtomicPartIdIndex();
    Map<int, AtomicPart*>::Query query;
    query.key = apartId;
    apartInd->get(query);

    if (query.found)
    {
        if (string(name) == "Q1")
        {
            set<int> locksRequired;
            set<DesignObj*> targets;
            targets.insert(query.val);
            ILSrv.getLockStack(query.val, &locksRequired);
            ILSrv.IntentionLock(tid, dataHolder, &targets,4, 0, &locksRequired);
            performOperationOnAtomicPart(query.val);
            ILSrv.IntentionUnlock(tid, &targets, 4, &locksRequired);
            // pthread_rwlock_t *lock = dominatorHelper::getIntentioninatorLock(dataHolder, &(min), &(max));
            // auto *inv = new interval(min, max, 0);
            // if (!domPool.IsOverlap(inv, 0, threadID)) {
            //     pthread_rwlock_rdlock(lock);
            //     performOperationOnAtomicPart(query.val);
            //     count++;
            //     pthread_rwlock_unlock(lock);
            //     domPool.Delete(threadID);
            // }
        }
        else if (string(name) == "OP9" || string(name) == "OP15")
        {
            set<int> locksRequired;
            set<DesignObj*> targets;
            targets.insert(query.val);
            ILSrv.getLockStack(query.val, &locksRequired);
            rerequest:
            ILSrv.IntentionLock(tid, dataHolder, &targets, 4,1, &locksRequired);
            performOperationOnAtomicPart(query.val);
            ILSrv.IntentionUnlock(tid, &targets, 4, &locksRequired);
            // pthread_rwlock_t *lock = dominatorHelper::getIntentioninatorLock(dataHolder, &min, &(max));
            // auto *inv = new interval(min, max, 1);
            // if (!domPool.IsOverlap(inv, 1, threadID)) {
            //     pthread_rwlock_wrlock(lock);
            //     performOperationOnAtomicPart(query.val);
            //     count++;
            //     pthread_rwlock_unlock(lock);
            //     domPool.Delete(threadID);
            // }
        }
    }
    else
    {
        Sb7Exception();
    }
    return count;
}

void sb7::IntentionQuery1::performOperationOnAtomicPart(AtomicPart* apart) const
{
    apart->nullOperation();
}

////////////
// Query2 //
////////////

sb7::IntentionQuery2::IntentionQuery2(DataHolder* dh, optype t, const char* n, int p)
    : Operation(t, n, dh)
{
    percent = p;
    //	maxAtomicDate = parameters.getMaxAtomicDate();
    //	minAtomicDate = parameters.getMaxAtomicDate() -
    //		percent * (parameters.getMaxAtomicDate() -
    //					parameters.getMinAtomicDate()) / 100;
}

int sb7::IntentionQuery2::run(int tid) const
{
    //ReadLockHandle readLockHandle(dom_lock_srv.getLock());
    return innerRun(tid);
}

int sb7::IntentionQuery2::innerRun(int tid) const
{
    int count = 0;
    long min = INTMAX_MAX, max = 0;

    int range = percent * (parameters.getMaxAtomicDate() -
        parameters.getMinAtomicDate()) / 100;
    int minA = get_random()->nextInt(parameters.getMaxAtomicDate() - range);
    int maxA = minA + range;

    Map<int, Set<AtomicPart*>*>* setInd =
        dataHolder->getAtomicPartBuildDateIndex();
    MapIterator<int, Set<AtomicPart*>*> iter =
        setInd->getRange(minA, maxA);

    while (iter.has_next())
    {
        Set<AtomicPart*>* apartSet = iter.next();
        SetIterator<AtomicPart*> apartIter = apartSet->getIter();
        set<DesignObj*> targets;
        set<int> locksRequired;
        set<int> handled;
        while (apartIter.has_next())
        {
            AtomicPart* apart = apartIter.next();
            ILSrv.getLockStack(apart, &locksRequired);
            targets.insert(apart);
        }
        int mode = 0;
        if (string(name) == "Q2")
            mode = 0;
        if (string(name) == "OP10")
            mode = 1;

        // sort(targets.begin(), targets.end(), [](const DesignObj* a, const DesignObj* b){return (a->getId()<b->getId());});


        ILSrv.IntentionLock(tid, dataHolder, &targets, 4,mode, &locksRequired);

        for (auto* apart : targets)
        {
            performOperationOnAtomicPart((AtomicPart*)apart);
            count++;
        }

        ILSrv.IntentionUnlock(tid, &targets, 4, &(locksRequired));
        // handled.insert(locksRequired[apart->getId()].begin(), locksRequired[apart->getId()].end());
        // pthread_rwlock_t *lock = dominatorHelper::getIntentioninatorLock(dataHolder, &(min), &(max));
        // auto *inv = new interval(min, max, mode);
        // if (!domPool.IsOverlap(inv, mode, tid)) {
        //     if (mode == 0) {
        //         pthread_rwlock_rdlock(lock);
        //     } else {
        //         pthread_rwlock_wrlock(lock);
        //     }
        //
        //     for (auto *apart: aparts) {
        //         performOperationOnAtomicPart(apart);
        //         count++;
        //     }
        //     pthread_rwlock_unlock(lock);
        //     domPool.Delete(tid);
        // }
    }
    return count;
}

void sb7::IntentionQuery2::performOperationOnAtomicPart(AtomicPart* apart) const
{
    apart->nullOperation();
}

////////////
// Query4 //
////////////

#define QUERY4_ITER 100

int sb7::IntentionQuery4::run(int tid) const
{
    //ReadLockHandle readLockHandle(dom_lock_srv.getLock());

    int ret = 0;

    for (int i = 0; i < QUERY4_ITER; i++)
    {
        // construct name of documentation for composite part
        int partId = get_random()->nextInt(parameters.getMaxCompParts()) + 1;
        // TODO move all these constants to separate header file
        ITOA(itoa_buf, partId);
        string title = "Composite Part #" + (string)itoa_buf;

        // search for document with that name
        Map<string, Document*>* docInd = dataHolder->getDocumentTitleIndex();
        Map<string, Document*>::Query query;
        query.key = title;
        docInd->get(query);

        if (query.found)
        {
            Document* doc = query.val;
            CompositePart* cpart = doc->getCompositePart();
            Bag<BaseAssembly*>* usedIn = cpart->getUsedIn();
            BagIterator<BaseAssembly*> iter = usedIn->getIter();

            while (iter.has_next())
            {
                BaseAssembly* bassm = iter.next();
                bassm->nullOperation();
                ret++;
            }
        }
    }

    return ret;
}

////////////
// Query5 //
////////////

int sb7::IntentionQuery5::run(int tid) const
{
    //ReadLockHandle readLockHandle(dom_lock_srv.getLock());
    int ret = 0;

    Map<int, BaseAssembly*>* bassmInd = dataHolder->getBaseAssemblyIdIndex();
    MapIterator<int, BaseAssembly*> iter = bassmInd->getAll();

    while (iter.has_next())
    {
        ret += checkBaseAssembly(iter.next());
    }

    return ret;
}

int sb7::IntentionQuery5::checkBaseAssembly(BaseAssembly* bassm) const
{
    int assmBuildDate = bassm->getBuildDate();
    Bag<CompositePart*>* cparts = bassm->getComponents();
    BagIterator<CompositePart*> iter = cparts->getIter();

    while (iter.has_next())
    {
        CompositePart* cpart = iter.next();

        if (cpart->getBuildDate() > assmBuildDate)
        {
            bassm->nullOperation();
            return 1;
        }
    }

    return 0;
}

////////////
// Query6 //
////////////

int sb7::IntentionQuery6::run(int tid) const
{
    //ReadLockHandle readLockHandle(dom_lock_srv.getLock());
    return checkComplexAssembly(dataHolder->getModule()->getDesignRoot());
}

int sb7::IntentionQuery6::checkAssembly(Assembly* assembly) const
{
    if (assembly->getType() == assembly_type_complex)
    {
        return checkComplexAssembly((ComplexAssembly*)assembly);
    }
    else
    {
        return checkBaseAssembly((BaseAssembly*)assembly);
    }
}

int sb7::IntentionQuery6::checkComplexAssembly(ComplexAssembly* assembly) const
{
    int ret = 0;

    Set<Assembly*>* subAssmSet = assembly->getSubAssemblies();
    SetIterator<Assembly*> iter = subAssmSet->getIter();

    while (iter.has_next())
    {
        ret += checkAssembly(iter.next());
    }

    if (ret)
    {
        assembly->nullOperation();
        ret++;
    }

    return ret;
}

////////////
// Query7 //
////////////

int sb7::IntentionQuery7::run(int tid) const
{
    //ReadLockHandle readLockHandle(dom_lock_srv.getLock());
    int ret = 0;

    Map<int, AtomicPart*>* apartInd = dataHolder->getAtomicPartIdIndex();
    MapIterator<int, AtomicPart*> iter = apartInd->getAll();

    while (iter.has_next())
    {
        AtomicPart* apart = iter.next();
        apart->nullOperation();
        ret++;
    }

    return ret;
}
