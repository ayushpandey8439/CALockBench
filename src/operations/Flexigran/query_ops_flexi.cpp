#include "query_ops_flexi.h"

#include "../../helpers.h"
#include "../../parameters.h"
#include "../../sb7_exception.h"
#include "./FlexiGranHelper.h"
#include "FlexiPool.h"

extern FlexiPool flexiPool;
extern int fgPercent;

////////////
// Query1 //
////////////

#define QUERY1_ITER 10

int FlexiQuery1::run(int tid) const
{
    //ReadLockHandle readLockHandle(Flexi_lock_srv.getLock());
    return innerRun(tid);
}

int FlexiQuery1::innerRun(int tid) const
{
    int count = 0;
    int threadID = tid;
    int min = INFINITY, max = -1, level = -1, granularity = 2;
    int lockNature = 1+ (rand() % 100);
    int apartId = get_random()->nextInt(
        parameters.getMaxAtomicParts()) + 1;
    Map<int, AtomicPart*>* apartInd = dataHolder->getAtomicPartIdIndex();
    Map<int, AtomicPart*>::Query query;
    query.key = apartId;
    apartInd->get(query);

    if (query.found && query.val->m_pre_number != 0 && query.val->m_post_number != 0)
    {
        min = query.val->m_pre_number;
        max = query.val->m_post_number;
        level = query.val->m_levelFromRoot;

        if (string(name) == "Q1")
        {
            if (lockNature < fgPercent)
            {
                granularity = 0;
            }
            else
            {
                granularity = 1;
            }


            pthread_rwlock_t* lock = FlexigranHelper::getFlexiLock(dataHolder, &(min), &(max), &(level));
            if (!flexiPool.doOverlap(min, max, 0, tid, granularity, level))
            {
                // pthread_rwlock_rdlock(lock);
                performOperationOnAtomicPart(query.val);
                count++;
                // pthread_rwlock_unlock(lock);
                flexiPool.unlockRange(threadID);
            }
        }
        else if (string(name) == "OP9" || string(name) == "OP15")
        {
            pthread_rwlock_t* lock = FlexigranHelper::getFlexiLock(dataHolder, &(min), &(max), &(level));
            if (!flexiPool.doOverlap(min, max, 1, tid, granularity, level))
            {
                // pthread_rwlock_wrlock(lock);
                performOperationOnAtomicPart(query.val);
                count++;
                // pthread_rwlock_unlock(lock);
                flexiPool.unlockRange(threadID);
            }
        }
    }
    else
    {
        Sb7Exception();
    }
    return count;
}

void FlexiQuery1::performOperationOnAtomicPart(AtomicPart* apart) const
{
    apart->nullOperation();
}

////////////
// Query2 //
////////////

FlexiQuery2::FlexiQuery2(DataHolder* dh, optype t, const char* n, int p)
    : Operation(t, n, dh)
{
    percent = p;
    //	maxAtomicDate = parameters.getMaxAtomicDate();
    //	minAtomicDate = parameters.getMaxAtomicDate() -
    //		percent * (parameters.getMaxAtomicDate() -
    //					parameters.getMinAtomicDate()) / 100;
}

int FlexiQuery2::run(int tid) const
{
    //ReadLockHandle readLockHandle(Flexi_lock_srv.getLock());
    return innerRun(tid);
}

int FlexiQuery2::innerRun(int tid) const
{
    int count = 0;
    int min = 0, max = 0, level = -1, granularity = 2;

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
        vector<AtomicPart*> aparts;
        while (apartIter.has_next())
        {
            AtomicPart* apart = apartIter.next();
            if (apart->m_pre_number != 0 && apart->m_post_number != 0)
            {
                if (min == 0 && max == 0)
                {
                    min = apart->m_pre_number;
                    max = apart->m_post_number;
                    level = apart->m_levelFromRoot;
                }
                else
                {
                    if (apart->m_pre_number < min)
                        min = apart->m_pre_number;
                    if (apart->m_post_number > max)
                        max = apart->m_post_number;
                }
                aparts.push_back(apart);
            }
        }
        int mode = 0;
        if (string(name) == "Q2")
            mode = 0;
        if (string(name) == "OP10")
            mode = 1;

        int lockNature = 1+ (rand() % 100);
        if (lockNature < fgPercent)
        {
            granularity = 0;
        }
        else
        {
            granularity = 1;
        }

        pthread_rwlock_t* lock = FlexigranHelper::getFlexiLock(dataHolder, &(min), &(max), &(mode));

        if (!flexiPool.doOverlap(min, max, mode, tid, granularity, level))
        {
            // if(mode==0)
            // {
            //     pthread_rwlock_rdlock(lock);
            // } else if(mode==1)
            // {
            //     pthread_rwlock_wrlock(lock);
            // }
            for (auto* apart : aparts)
            {
                performOperationOnAtomicPart(apart);
                count++;
            }
            // pthread_rwlock_unlock(lock);
            flexiPool.unlockRange(tid);
        }
    }
    return count;
}

void FlexiQuery2::performOperationOnAtomicPart(AtomicPart* apart) const
{
    apart->nullOperation();
}

////////////
// Query4 //
////////////

#define QUERY4_ITER 100

int FlexiQuery4::run(int tid) const
{
    //ReadLockHandle readLockHandle(Flexi_lock_srv.getLock());

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

int FlexiQuery5::run(int tid) const
{
    //ReadLockHandle readLockHandle(Flexi_lock_srv.getLock());
    int ret = 0;

    Map<int, BaseAssembly*>* bassmInd = dataHolder->getBaseAssemblyIdIndex();
    MapIterator<int, BaseAssembly*> iter = bassmInd->getAll();

    while (iter.has_next())
    {
        ret += checkBaseAssembly(iter.next());
    }

    return ret;
}

int FlexiQuery5::checkBaseAssembly(BaseAssembly* bassm) const
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

int FlexiQuery6::run(int tid) const
{
    //ReadLockHandle readLockHandle(Flexi_lock_srv.getLock());
    return checkComplexAssembly(dataHolder->getModule()->getDesignRoot());
}

int FlexiQuery6::checkAssembly(Assembly* assembly) const
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

int FlexiQuery6::checkComplexAssembly(ComplexAssembly* assembly) const
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

int FlexiQuery7::run(int tid) const
{
    //ReadLockHandle readLockHandle(Flexi_lock_srv.getLock());
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
