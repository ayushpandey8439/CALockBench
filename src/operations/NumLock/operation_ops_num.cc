#include "operation_ops_num.h"

#include "../../parameters.h"
#include "../../sb7_exception.h"
#include "../../thread/thread.h"
#include "NumPool.h"
#include "numHelper.h"

extern NumPool midPool;

int sb7::NumOperation6::run(int tid) const {
    //ReadLockHandle readLockHandle(dom_lock_srv.getLock());
    return innerRun(tid);
}

int sb7::NumOperation6::innerRun(int tid) const {
    // Generate one random number that is in range of possible complex assembly
    // identifiers. It is used to look up complex assembly.
    //
    // TODO try to figure out how to generate these ids in a more precise way
    // so this operation fails only if it is really
    //
    int cassmId = get_random()->nextInt(
            parameters.getMaxComplexAssemblies()) + 1;

    // lookup complex assembly using complex assembly index
    Map<int, ComplexAssembly *> *cassmInd =
            dataHolder->getComplexAssemblyIdIndex();
    Map<int, ComplexAssembly *>::Query query;
    query.key = cassmId;
    cassmInd->get(query);

    // If complex assembly is not found throw an exception.
    // This is an easy way to get out of the transaction.
    if (!query.found || query.val->m_pre_number == 0 || query.val->m_post_number == 0) {
        throw Sb7Exception();
    }

    int ret;

    // if complex assembly was found process it
    ComplexAssembly *cassm = query.val;
    ComplexAssembly *superAssm = cassm->getSuperAssembly();

    // if this assembly is root perform operation on it
    if (superAssm == NULL || superAssm->m_pre_number == 0 || superAssm->m_post_number == 0) {
        float min = INFINITY, max = 0;
        min = cassm->m_pre_number;
        max = cassm->m_post_number;
        float rlm_min, rlm_max;
        pthread_rwlock_t *lock = NumHelper::getNumLock(dataHolder, &(min), &(max));
        auto *inv = new numInterval(min, max,0);
        if (!midPool.IsOverlap(inv, 0, tid)) {
            pthread_rwlock_rdlock(lock);
            performOperationOnComplexAssembly(cassm);
            pthread_rwlock_unlock(lock);
            ret = 1;
            midPool.Delete(tid);
        }
        ret = 0;
    } else {
        // else perform operation on all it's siblings (including itself)
        Set<Assembly *> *siblingAssms = superAssm->getSubAssemblies();
        SetIterator<Assembly *> iter = siblingAssms->getIter();
        ret = 0;
        float min = INFINITY, max = 0;
        min = superAssm->m_pre_number;
        max = superAssm->m_post_number;
        float rlm_min, rlm_max;
        pthread_rwlock_t *lock = NumHelper::getNumLock(dataHolder, &(min), &(max));
        auto *inv = new numInterval(min, max,0);
        if (!midPool.IsOverlap(inv, 0, tid)) {
            pthread_rwlock_rdlock(lock);
            while (iter.has_next()) {
                performOperationOnComplexAssembly((ComplexAssembly *) iter.next());
                ret++;
            }
            pthread_rwlock_unlock(lock);
            midPool.Delete(tid);
        }
    }

    return ret;
}

void sb7::NumOperation6::performOperationOnComplexAssembly(
        ComplexAssembly *cassm) const {
    cassm->nullOperation();
}

////////////////
// Operation7 //
////////////////

int sb7::NumOperation7::run(int tid) const {
    //ReadLockHandle readLockHandle(dom_lock_srv.getLock());
    return innerRun(tid);
}

int sb7::NumOperation7::innerRun(int tid) const {
    // Generate one random number that is in range of possible base assembly
    // identifiers. It is used to look up base assembly from index.
    //
    // TODO try to figure out how to generate these ids in a more precise way
    // so this operation fails only if it is really
    //
    int bassmId = get_random()->nextInt(parameters.getMaxBaseAssemblies()) + 1;

    // lookup base assembly using base assembly index
    Map<int, BaseAssembly *> *bassmInd = dataHolder->getBaseAssemblyIdIndex();
    Map<int, BaseAssembly *>::Query query;
    query.key = bassmId;
    bassmInd->get(query);

    if (!query.found || query.val->m_pre_number == 0 || query.val->m_post_number == 0) {
        throw Sb7Exception();
    }

    // process all sibling base assemblies
    ComplexAssembly *superAssm = query.val->getSuperAssembly();
    Set<Assembly *> *siblingSet = superAssm->getSubAssemblies();
    SetIterator<Assembly *> iter = siblingSet->getIter();
    int ret = 0;

    float min = INFINITY, max = 0;
    min = superAssm->m_pre_number;
    max = superAssm->m_post_number;
    float rlm_min, rlm_max;
    pthread_rwlock_t *lock = NumHelper::getNumLock(dataHolder, &(min), &(max));
    auto *inv = new numInterval(min, max,0);

    if (!midPool.IsOverlap(inv, 0, tid)) {
        pthread_rwlock_rdlock(lock);
        while (iter.has_next()) {
            performOperationOnBaseAssembly((BaseAssembly *) iter.next());
            ret++;
        }
        pthread_rwlock_unlock(lock);
        midPool.Delete(tid);
    }


    return ret;
}

void sb7::NumOperation7::performOperationOnBaseAssembly(
        BaseAssembly *bassm) const {
    bassm->nullOperation();
}

////////////////
// Operation8 //
////////////////

int sb7::NumOperation8::run(int tid) const {
    //ReadLockHandle readLockHandle(dom_lock_srv.getLock());
    return innerRun(tid);
}

int sb7::NumOperation8::innerRun(int tid) const {
    // Generate one random number that is in range of possible base assembly
    // identifiers. It is used to look up base assembly from index.
    //
    // TODO try to figure out how to generate these ids in a more precise way
    // so this operation fails only if it is really
    //
    int bassmId = get_random()->nextInt(
            parameters.getMaxBaseAssemblies()) + 1;

    // lookup base assembly using base assembly index
    Map<int, BaseAssembly *> *bassmInd = dataHolder->getBaseAssemblyIdIndex();
    Map<int, BaseAssembly *>::Query query;
    query.key = bassmId;
    bassmInd->get(query);

    if (!query.found) {
        throw Sb7Exception();
    }

    Bag<CompositePart *> *componentBag = query.val->getComponents();
    BagIterator<CompositePart *> iter = componentBag->getIter();
    int ret = 0;

    list<CompositePart *> cparts;
    float min = 0, max = 0;

    while (iter.has_next()) {
        CompositePart *cpart = iter.next();
        if (cpart->m_pre_number != 0) {
            cparts.push_back(cpart);
            if (min == 0 || min < cpart->m_pre_number) {
                min = cpart->m_pre_number;
            }
            if (max == 0 || max > cpart->m_post_number) {
                max = cpart->m_post_number;
            }
        }
    }

    float rlm_min, rlm_max;
    pthread_rwlock_t *lock = NumHelper::getNumLock(dataHolder, &(min), &(max));
    auto *inv = new numInterval(min, max,0);
    if (!midPool.IsOverlap(inv, 0, tid)) {
        for (auto *cpart: cparts) {
            performOperationOnComponent(cpart);
            ret++;
        }
        midPool.Delete(tid);
    }

    return ret;
}

void sb7::NumOperation8::performOperationOnComponent(CompositePart *comp) const {
    comp->nullOperation();
}

////////////////
// Operation9 //
////////////////

int sb7::NumOperation9::run(int tid) const {
    //WriteLockHandle writeLockHandle(dom_lock_srv.getLock());
    return NumQuery1::innerRun(tid);
}

void sb7::NumOperation9::performOperationOnAtomicPart(AtomicPart *apart) const {
    apart->swapXY();
}

////////////////
// Operation10 //
////////////////

int sb7::NumOperation10::run(int tid) const {
    //WriteLockHandle writeLockHandle(dom_lock_srv.getLock());
    return NumQuery2::innerRun(tid);
}

void sb7::NumOperation10::performOperationOnAtomicPart(AtomicPart *apart) const {
    apart->swapXY();
}
//
///////////////////
//// Operation11 //
///////////////////
//
//#define MANUAL_TEXT_START_1 'I'
//#define MANUAL_TEXT_START_2 'i'
//
//int sb7::NumOperation11::run(int tid) const {
//    //WriteLockHandle writeLockHandle(dom_lock_srv.getLock());
//    return NumTraversal8::traverse(dataHolder->getModule()->getManual());
//}
//
//int sb7::NumOperation11::traverse(Manual *manual) const {
//    int ret;
//
//    if (manual->startsWith(MANUAL_TEXT_START_1)) {
//        ret = manual->replaceChar(MANUAL_TEXT_START_1, MANUAL_TEXT_START_2);
//    } else if (manual->startsWith(MANUAL_TEXT_START_2)) {
//        ret = manual->replaceChar(MANUAL_TEXT_START_2, MANUAL_TEXT_START_1);
//    } else {
//        throw Sb7Exception("OP11: unexpected Manual.text!");
//    }
//
//    return ret;
//}

/////////////////
// Operation12 //
/////////////////

int sb7::NumOperation12::run(int tid) const {
    //WriteLockHandle writeLockHandle(dom_lock_srv.getLock());
    return NumOperation6::innerRun(tid);
}

void sb7::NumOperation12::performOperationOnComplexAssembly(
        ComplexAssembly *cassm) const {
    cassm->updateBuildDate();
}

/////////////////
// Operation13 //
/////////////////

int sb7::NumOperation13::run(int tid) const {
    //WriteLockHandle writeLockHandle(dom_lock_srv.getLock());
    return NumOperation7::innerRun(tid);
}

void sb7::NumOperation13::performOperationOnBaseAssembly(
        BaseAssembly *bassm) const {
    bassm->updateBuildDate();
}

/////////////////
// Operation14 //
/////////////////

int sb7::NumOperation14::run(int tid) const {
    //WriteLockHandle writeLockHandle(dom_lock_srv.getLock());
    return NumOperation8::innerRun(tid);
}

void sb7::NumOperation14::performOperationOnComponent(
        CompositePart *cpart) const {
    cpart->updateBuildDate();
}

/////////////////
// Operation15 //
/////////////////

int sb7::NumOperation15::run(int tid) const {
    //WriteLockHandle writeLockHandle(dom_lock_srv.getLock());
    return NumQuery1::innerRun(tid);
}

void sb7::NumOperation15::performOperationOnAtomicPart(AtomicPart *apart) const {
    dataHolder->removeAtomicPartFromBuildDateIndex(apart);
    apart->updateBuildDate();
    dataHolder->addAtomicPartToBuildDateIndex(apart);
}
