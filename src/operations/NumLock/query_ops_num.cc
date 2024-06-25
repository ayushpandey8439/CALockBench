#include "query_ops_num.h"
#include<iostream>
#include "../../helpers.h"
#include "../../containers.h"
#include "../../parameters.h"
#include "../../struct/assembly.h"
#include "../../thread/thread.h"
#include<pthread.h>
#include <stdio.h>
#include "NumPool.h"
#include "numHelper.h"
#include "../../sb7_exception.h"
#include <vector>
////////////
// Query1 //
////////////
#define QUERY1_ITER 10
// Anju - try to use numNodesLocked via command line arg.

extern NumPool midPool;
extern int numBuckets;
extern int numIterations;
extern int numNodesLocked;

/*extern int falseSubsumptionCount;
extern int *fsCountArray;
extern int *correctedFScountArray; */

int sb7::NumQuery1::run(int tid) const {
    //ReadLockHandle smLockHandle(lm_lock_srv.getStructureModificationLock());
    //ReadLockHandle apartLockHandle(lm_lock_srv.getAtomicPartLock());
//cout<<"/n name is"<<name;
    return innerRun(tid);
}

int sb7::NumQuery1::innerRun(int tid) const {
    int count = 0;
    int threadID = tid;
    float min = INFINITY, max = -1;
    int apartId = get_random()->nextInt(
            parameters.getMaxAtomicParts()) + 1;
    Map<int, AtomicPart *> *apartInd = dataHolder->getAtomicPartIdIndex();
    Map<int, AtomicPart *>::Query query;
    query.key = apartId;
    apartInd->get(query);

    if (query.found && query.val->m_pre_number != 0 && query.val->m_post_number != 0) {
        if ((((query.val)->getPartOf())->getUsedIn())->size() != 0)// if not a disconnected composite part
        {
            if (min == 0 && max == 0) {
                min = (query.val)->m_pre_number;
                max = (query.val)->m_post_number;
            } else {
                if ((query.val)->m_pre_number < min)
                    min = (query.val)->m_pre_number;
                if ((query.val)->m_post_number > max)
                    max = (query.val)->m_post_number;
            }
        }

        if (string(name) == "Q1") {
            float rlm_min, rlm_max;
            pthread_rwlock_t *lock = NumHelper::getNumLock(dataHolder, &(min), &(max));
            auto *inv = new numInterval(min, max, 0);
            if (!midPool.IsOverlap(inv, 0, threadID)) {
                pthread_rwlock_rdlock(lock);
                performOperationOnAtomicPart(query.val);
                count++;
                pthread_rwlock_unlock(lock);
                midPool.Delete(threadID);
            }
        } else if (string(name) == "OP9" || string(name) == "OP15") {
            float rlm_min, rlm_max;
            pthread_rwlock_t *lock = NumHelper::getNumLock(dataHolder, &min, &(max));
            auto *inv = new numInterval(min, max, 1);
            if (!midPool.IsOverlap(inv, 1, threadID)) {
                pthread_rwlock_wrlock(lock);
                performOperationOnAtomicPart(query.val);
                count++;
                pthread_rwlock_unlock(lock);
                midPool.Delete(threadID);
            }
        }
    } else {
        Sb7Exception();
    }
    return count;
}

void sb7::NumQuery1::performOperationOnAtomicPart(AtomicPart *apart) const {
//Anju adding for trial:
    int x;
    for (int i = 0; i < numIterations; i++) {
        x += i;
    }

//************************************************************************************************
//if(((apart -> getPartOf()) -> getUsedIn())->size() != 0)
//cout<<"\n pre post "<< apart -> m_pre_number <<" -- "<< apart -> m_post_number <<"\n";
//************************************************************************************************
    apart->nullOperation();
}

////////////
// Query2 //
////////////

sb7::NumQuery2::NumQuery2(DataHolder *dh, optype t, const char *n, int p)
        : Operation(t, n, dh) {
    percent = p;
    maxAtomicDate = parameters.getMaxAtomicDate();
    minAtomicDate = parameters.getMaxAtomicDate() -
                    percent * (parameters.getMaxAtomicDate() -
                               parameters.getMinAtomicDate()) / 100;
}

int sb7::NumQuery2::run(int tid) const {
    //ReadLockHandle smLockHandle(lm_lock_srv.getStructureModificationLock());
    //ReadLockHandle apartLockHandle(lm_lock_srv.getAtomicPartLock());

    return innerRun(tid);
}

int sb7::NumQuery2::innerRun(int tid) const {
    int count = 0;
    float min = 0, max = 0;

    int range = percent * (parameters.getMaxAtomicDate() -
                           parameters.getMinAtomicDate()) / 100;
    int minA = get_random()->nextInt(parameters.getMaxAtomicDate() - range);
    int maxA = minA + range;

    Map<int, Set<AtomicPart *> *> *setInd =
            dataHolder->getAtomicPartBuildDateIndex();
    MapIterator<int, Set<AtomicPart *> *> iter =
            setInd->getRange(minA, maxA);

    while (iter.has_next()) {
        Set<AtomicPart *> *apartSet = iter.next();
        SetIterator<AtomicPart *> apartIter = apartSet->getIter();
        vector<AtomicPart *> aparts;
        while (apartIter.has_next()) {
            AtomicPart *apart = apartIter.next();
            if (apart->m_pre_number != 0 && apart->m_post_number != 0) {
                if (min == 0 && max == 0) {
                    min = apart->m_pre_number;
                    max = apart->m_post_number;
                } else {
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
        float rlm_min, rlm_max;
        pthread_rwlock_t *lock = NumHelper::getNumLock(dataHolder, &(min), &(max));
        auto *inv = new numInterval(min, max, mode);
        if (!midPool.IsOverlap(inv, mode, tid)) {
            if (mode == 0) {
                pthread_rwlock_rdlock(lock);
            } else {
                pthread_rwlock_wrlock(lock);
            }

            for (auto *apart: aparts) {
                performOperationOnAtomicPart(apart);
                count++;
            }
            pthread_rwlock_unlock(lock);
            midPool.Delete(tid);
        }
    }
    return count;
}

void sb7::NumQuery2::performOperationOnAtomicPart(AtomicPart *apart) const {
    apart->nullOperation();
}

////////////
// Query4 //
//////////////
//
//#define QUERY4_ITER 100
//
//int sb7::NumQuery4::run(int tid) const {
////    ReadLockHandle smLockHandle(lm_lock_srv.getStructureModificationLock());
////    ReadLockHandle bassmLockHandle(lm_lock_srv.getBaseAssemblyLock());
//
//    int ret = 0;
//
//    for(int i = 0;i < QUERY4_ITER;i++) {
//        // construct name of documentation for composite part
//        int partId = get_random()->nextInt(parameters.getMaxCompParts()) + 1;
//        // TODO move all these constants to separate header file
//        ITOA(itoa_buf, partId);
//        string title = "Composite Part #" + (string)itoa_buf;
//
//        // search for document with that name
//        Map<string, Document *> *docInd = dataHolder->getDocumentTitleIndex();
//        Map<string, Document *>::Query query;
//        query.key = title;
//        docInd->get(query);
//
//        if(query.found) {
//            Document *doc = query.val;
//            CompositePart *cpart = doc->getCompositePart();
//            Bag<BaseAssembly *> *usedIn = cpart->getUsedIn();
//            BagIterator<BaseAssembly *> iter = usedIn->getIter();
//
//            while(iter.has_next()) {
//                BaseAssembly *bassm = iter.next();
//                bassm->nullOperation();
//                ret++;
//            }
//        }
//    }
//
//    return ret;
//}
//
//////////////
//// Query5 //
//////////////
//
//int sb7::NumQuery5::run(int tid) const {
//    ReadLockHandle smLockHandle(lm_lock_srv.getStructureModificationLock());
//    ReadLockHandle bassmLockHandle(lm_lock_srv.getBaseAssemblyLock());
//    ReadLockHandle cpartLockHandle(lm_lock_srv.getCompositePartLock());
//
//    int ret = 0;
//
//    Map<int, BaseAssembly *> *bassmInd = dataHolder->getBaseAssemblyIdIndex();
//    MapIterator<int, BaseAssembly *> iter = bassmInd->getAll();
//
//    while(iter.has_next()) {
//        ret += checkBaseAssembly(iter.next());
//    }
//
//    return ret;
//}
//
//int sb7::NumQuery5::checkBaseAssembly(BaseAssembly *bassm) const {
//    int assmBuildDate = bassm->getBuildDate();
//    Bag<CompositePart *> *cparts = bassm->getComponents();
//    BagIterator<CompositePart *> iter = cparts->getIter();
//
//    while(iter.has_next()) {
//        CompositePart *cpart = iter.next();
//
//        if(cpart->getBuildDate() > assmBuildDate) {
//            bassm->nullOperation();
//            return 1;
//        }
//    }
//
//    return 0;
//}
//
//////////////
//// Query6 //
//////////////
//
//int sb7::NumQuery6::run(int tid) const {
//    ReadLockHandle smLockHandle(lm_lock_srv.getStructureModificationLock());
//    ReadLockHandle assmLockHandle(lm_lock_srv.getAssemblyLockArray());
//    ReadLockHandle cpartLockHandle(lm_lock_srv.getCompositePartLock());
//
//    return checkComplexAssembly(dataHolder->getModule()->getDesignRoot());
//}
//
//int sb7::NumQuery6::checkAssembly(Assembly *assembly) const {
//    if(assembly->getType() == assembly_type_complex) {
//        return checkComplexAssembly((ComplexAssembly *)assembly);
//    } else {
//        return checkBaseAssembly((BaseAssembly *)assembly);
//    }
//}
//
//int sb7::NumQuery6::checkComplexAssembly(ComplexAssembly *assembly) const {
//    int ret = 0;
//
//    Set<Assembly *> *subAssmSet = assembly->getSubAssemblies();
//    SetIterator<Assembly *> iter = subAssmSet->getIter();
//
//    while(iter.has_next()) {
//        ret += checkAssembly(iter.next());
//    }
//
//    if(ret) {
//        assembly->nullOperation();
//        ret++;
//    }
//
//    return ret;
//}
//
//////////////
//// Query7 //
//////////////
//
//int sb7::NumQuery7::run(int tid) const {
//    ReadLockHandle smLockHandle(lm_lock_srv.getStructureModificationLock());
//    ReadLockHandle apartLockHandle(lm_lock_srv.getAtomicPartLock());
//
//    int ret = 0;
//
//    Map<int, AtomicPart *> *apartInd = dataHolder->getAtomicPartIdIndex();
//    MapIterator<int, AtomicPart *> iter = apartInd->getAll();
//
//    while(iter.has_next()) {
//        AtomicPart *apart = iter.next();
//        apart->nullOperation();
//        ret++;
//    }
//
//    return ret;
//}
