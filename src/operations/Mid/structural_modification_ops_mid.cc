#include "structural_modification_ops_mid.h"

#include "../../parameters.h"
#include "../../sb7_exception.h"
#include "../../thread/thread.h"
#include "MidPool.h"
#include "MidHelper.h"
#include<pthread.h>
#include "../../labelling/Mid/MidLabeling.h"

extern MidPool midPool;
/////////////////////////////
// StructuralModification1 //
/////////////////////////////

int sb7::MidStructuralModification1::run(int tid) const {
    //WriteLockHandle writeLockHandle(dom_lock_srv.getLock());
    dataHolder->createCompositePart();
    return 1;
}

/////////////////////////////
// StructuralModification2 //
/////////////////////////////

int sb7::MidStructuralModification2::run(int tid) const {
    //WriteLockHandle writeLockHandle(dom_lock_srv.getLock());

    // generate random composite part id and try to look it up
    int cpartId = get_random()->nextInt(parameters.getMaxCompParts()) + 1;
    CompositePart *cpart = dataHolder->getCompositePart(cpartId);

    if (cpart == NULL || cpart->m_post_number == 0 || cpart->m_pre_number == 0) {
        throw Sb7Exception();
    }
    auto root = dataHolder->getModule()->getDesignRoot();
    float min = root->m_pre_number;
    float max = root->m_post_number;

    float rlm_min, rlm_max;
    pthread_rwlock_t *lock = MidHelper::getMidLock(dataHolder, &(min), &(max), &(rlm_min), &(rlm_max));
    auto *inv = new midInterval(min, max, rlm_min, rlm_max, 1);
    if (!midPool.IsOverlap(inv, 1, tid, dataHolder)) {
        pthread_rwlock_wrlock(lock);
        dataHolder->deleteCompositePart(cpart);
        auto *dfs = new MidTraversalDFS(dataHolder);
        auto *rdfs = new MidTraversalReverseDFS(dataHolder);
        auto t1 = std::chrono::high_resolution_clock::now();
        dfs->traverse(dataHolder->getModule()->getDesignRoot());
        rdfs->traverse(dataHolder->getModule()->getDesignRoot());
        auto t2 = std::chrono::high_resolution_clock::now();
        midPool.modificationTime += (t2 - t1);


        pthread_rwlock_unlock(lock);
        midPool.Delete(tid);
    }
    return 1;
}

/////////////////////////////
// StructuralModification3 //
/////////////////////////////

int sb7::MidStructuralModification3::run(int tid) const {
    // generate random composite part id
    int cpartId = get_random()->nextInt(parameters.getMaxCompParts()) + 1;
    CompositePart *cpart = dataHolder->getCompositePart(cpartId);

    if (cpart == NULL || cpart->m_pre_number == 0 || cpart->m_post_number == 0) {
        throw Sb7Exception();
    }

    // generate random base assembly id
    int bassmId = get_random()->nextInt(parameters.getMaxBaseAssemblies()) + 1;
    BaseAssembly *bassm = dataHolder->getBaseAssembly(bassmId);

    if (bassm == NULL || bassm->m_pre_number == 0 || bassm->m_post_number == 0) {
        throw Sb7Exception();
    }

    auto root = dataHolder->getModule()->getDesignRoot();
    float min = root->m_pre_number;
    float max = root->m_post_number;
//    if (root->m_pre_number < min)
//        min = cpart->m_pre_number;
//    if (cpart->m_post_number > max)
//        max = cpart->m_post_number;

    float rlm_min, rlm_max;
    pthread_rwlock_t *lock = MidHelper::getMidLock(dataHolder, &(min), &(max), &(rlm_min), &(rlm_max));
    auto *inv = new midInterval(min, max, rlm_min, rlm_max, 1);
    if (!midPool.IsOverlap(inv, 1, tid, dataHolder)) {
        pthread_rwlock_wrlock(lock);
        bassm->addComponent(cpart);

        auto t1 = std::chrono::high_resolution_clock::now();
        auto *dfs = new MidTraversalDFS(dataHolder);
        auto *rdfs = new MidTraversalReverseDFS(dataHolder);
        dfs->traverse(dataHolder->getModule()->getDesignRoot());
        rdfs->traverse(dataHolder->getModule()->getDesignRoot());
        auto t2 = std::chrono::high_resolution_clock::now();

//        bool didIntervalChange = false;
//        if (cpart->m_pre_number < bassm->m_pre_number) {
//            bassm->m_pre_number = cpart->m_pre_number;
//            didIntervalChange = true;
//        }
//        if (bassm->m_post_number < cpart->m_post_number) {
//            bassm->m_post_number = cpart->m_post_number;
//            didIntervalChange = true;
//        }
//        if (didIntervalChange) {
//            // Now, do the midInterval updates to ancestors of bassm
//            ComplexAssembly *cassm = bassm->getSuperAssembly();
//            while (didIntervalChange) // Remember to use break statement inside
//            {
//                didIntervalChange = false;
//                if (cassm->m_pre_number > cpart->m_pre_number) {
//                    cassm->m_pre_number = cpart->m_pre_number;
//                    didIntervalChange = true;
//                }
//                if (cassm->m_post_number < cpart->m_post_number) {
//                    cassm->m_post_number = cpart->m_post_number;
//                    didIntervalChange = true;
//                }
//                if ((cassm->m_pre_number == min) && (cassm->m_post_number == max)) {
//                    // Reached dominator. No need to go further up.
//                    break;
//                }
//                cassm = cassm->getSuperAssembly(); // Pointer to parent
//            }
//        }


        midPool.modificationTime += (t2 - t1);
//        midPool.count.fetch_add(1);
        pthread_rwlock_unlock(lock);
        midPool.Delete(tid);
    }
    return 1;
}
//
///////////////////////////////
//// StructuralModification4 //
///////////////////////////////
//
//int sb7::MidStructuralModification4::run(int tid) const {
//    int cassmId = get_random()->nextInt(parameters.getMaxComplexAssemblies()) + 1;
//    cassmId = (cassmId * (tid + 1)) % parameters.getMaxComplexAssemblies();
//    ComplexAssembly *cassm = dataHolder->getComplexAssembly(cassmId);
//    if (cassm == nullptr || cassm->isDeleted) {
//        throw Sb7Exception();
//    }
//
//    float min = dataHolder->getModule()->getDesignRoot()->m_pre_number;
//    float max = dataHolder->getModule()->getDesignRoot()->m_post_number;
//    float rlm_min, rlm_max;
//    pthread_rwlock_t *lock = MidHelper::getMidLock(dataHolder, &(min), &(max), &(rlm_min), &(rlm_max));
//    auto *inv = new midInterval(min, max, rlm_min, rlm_max, 1);
//
//    if (!midPool.IsOverlap(inv, 1, tid, dataHolder)) {
//        dataHolder->createSubAssembly(dataHolder->getModule()->getDesignRoot(), 1);
//        auto *r = new MidLockRelabeling(dataHolder);
//        auto t1 = std::chrono::high_resolution_clock::now();
//        r->traverse(dataHolder->getModule()->getDesignRoot());
//        auto t2 = std::chrono::high_resolution_clock::now();
//        midPool.modificationTimeMid += (t2 - t1);
//        midPool.count.fetch_add(1);
//        midPool.Delete(tid);
//    }
//    return 0;
//}
//
///////////////////////////////
//// StructuralModification5 //
///////////////////////////////
//
//int sb7::MidStructuralModification5::run(int tid) const {
//    float min = dataHolder->getModule()->getDesignRoot()->m_pre_number;
//    float max = dataHolder->getModule()->getDesignRoot()->m_post_number;
//    float rlm_min, rlm_max;
//    pthread_rwlock_t *lock = MidHelper::getMidLock(dataHolder, &(min), &(max), &(rlm_min), &(rlm_max));
//    auto *inv = new midInterval(min, max, rlm_min, rlm_max, 1);
//
//    if (!midPool.IsOverlap(inv, 1, tid, dataHolder)) {
//        dataHolder->createSubAssembly(dataHolder->getModule()->getDesignRoot(), 1);
//        auto *r = new MidLockRelabeling(dataHolder);
//        auto t1 = std::chrono::high_resolution_clock::now();
//        r->traverse(dataHolder->getModule()->getDesignRoot());
//        auto t2 = std::chrono::high_resolution_clock::now();
//        midPool.modificationTimeMid += (t2 - t1);
//        midPool.count.fetch_add(1);
//        midPool.Delete(tid);
//    }
//    return 0;
//}
//
///////////////////////////////
//// StructuralModification6 //
///////////////////////////////
//
//int sb7::MidStructuralModification6::run(int tid) const {
//    //WriteLockHandle writeLockHandle(dom_lock_srv.getLock());
//
//    // generate random base assembly id
//    int bassmId = get_random()->nextInt(
//            parameters.getMaxBaseAssemblies()) + 1;
//    BaseAssembly *bassm = dataHolder->getBaseAssembly(bassmId);
//
//    if (bassm == NULL) {
//        throw Sb7Exception();
//    }
//
//    // get parent and check that it has at least one more child
//    ComplexAssembly *cassm = bassm->getSuperAssembly();
//    Set<Assembly *> *subAssmSet = cassm->getSubAssemblies();
//
//    // don't let the tree break
//    if (subAssmSet->size() == 1) {
//        throw Sb7Exception();
//    }
//    float min = cassm->m_pre_number;
//    float max = cassm->m_post_number;
//    float rlm_min, rlm_max;
//    pthread_rwlock_t *lock = MidHelper::getMidLock(dataHolder, &(min), &(max), &(rlm_min), &(rlm_max));
//    auto *inv = new midInterval(min, max, rlm_min, rlm_max, 1);
//
//    if (!midPool.IsOverlap(inv, 1, tid, dataHolder)) {
//        dataHolder->deleteBaseAssembly(bassm);
//        auto *r = new MidLockRelabeling(dataHolder);
//        r->traverse(dataHolder->getModule()->getDesignRoot());
//        midPool.Delete(tid);
//    }
//
//    return 0;
//}
//
///////////////////////////////
//// StructuralModification7 //
///////////////////////////////
//
//int sb7::MidStructuralModification7::run(int tid) const {
//    //WriteLockHandle writeLockHandle(dom_lock_srv.getLock());
//
//    // generate random complex assembly id
//    int cassmId = get_random()->nextInt(
//            parameters.getMaxComplexAssemblies()) + 1;
//    ComplexAssembly *cassm = dataHolder->getComplexAssembly(cassmId);
//
//    if (cassm == NULL) {
//        throw Sb7Exception();
//    }
//    float min = cassm->m_pre_number;
//    float max = cassm->m_post_number;
//    float rlm_min, rlm_max;
//    pthread_rwlock_t *lock = MidHelper::getMidLock(dataHolder, &(min), &(max), &(rlm_min), &(rlm_max));
//    auto *inv = new midInterval(min, max, rlm_min, rlm_max, 1);
//
//    if (!midPool.IsOverlap(inv, 1, tid, dataHolder)) {
//        // create sub assembly
//        dataHolder->createSubAssembly(cassm, parameters.getNumAssmPerAssm());
//        auto *r = new MidLockRelabeling(dataHolder);
//        r->traverse(dataHolder->getModule()->getDesignRoot());
//        midPool.Delete(tid);
//    }
//
//
//    return 1;
//}
//
///////////////////////////////
//// StructuralModification8 //
///////////////////////////////
//
//int sb7::MidStructuralModification8::run(int tid) const {
//    //WriteLockHandle writeLockHandle(dom_lock_srv.getLock());
//
//    // generate random complex assembly id
//    int cassmId = get_random()->nextInt(
//            parameters.getMaxComplexAssemblies()) + 1;
//    ComplexAssembly *cassm = dataHolder->getComplexAssembly(cassmId);
//
//    if (cassm == NULL) {
//        throw Sb7Exception();
//    }
//
//    // get super assembly
//    ComplexAssembly *superAssm = cassm->getSuperAssembly();
//
//    // don't continue if we got root complex assembly
//    if (superAssm == NULL) {
//        throw Sb7Exception();
//    }
//
//    // check if this would break the tree structure
//    Set<Assembly *> *assmSet = superAssm->getSubAssemblies();
//
//    if (assmSet->size() == 1) {
//        throw Sb7Exception();
//    }
//    float min = superAssm->m_pre_number;
//    float max = superAssm->m_post_number;
//    float rlm_min, rlm_max;
//    pthread_rwlock_t *lock = MidHelper::getMidLock(dataHolder, &(min), &(max), &(rlm_min), &(rlm_max));
//    auto *inv = new midInterval(min, max, rlm_min, rlm_max, 1);
//    if (!midPool.IsOverlap(inv, 1, tid)) {
//        // delete selected complex assembly
//        dataHolder->deleteComplexAssembly(cassm);
//        auto *r = new MidLockRelabeling(dataHolder);
//        r->traverse(dataHolder->getModule()->getDesignRoot());
//        midPool.Delete(tid);
//    }
//
//
//    return 1;
//}
