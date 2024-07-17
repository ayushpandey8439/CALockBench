#include "structural_modification_ops_intention.h"

#include "Intention_lock_srv.h"
#include "../../parameters.h"
#include "../../sb7_exception.h"
#include "../../thread/thread.h"

extern Intention_lock_srv ILSrv;

/////////////////////////////
// StructuralModification1 //
/////////////////////////////

int sb7::IntentionStructuralModification1::run(int tid) const {
    //WriteLockHandle writeLockHandle(dom_lock_srv.getLock());
    dataHolder->createCompositePart();
    return 0;
}

/////////////////////////////
// StructuralModification2 //
/////////////////////////////

int sb7::IntentionStructuralModification2::run(int tid) const {
    //WriteLockHandle writeLockHandle(dom_lock_srv.getLock());

    // generate random composite part id and try to look it up
    int cpartId = get_random()->nextInt(parameters.getMaxCompParts()) + 1;
    CompositePart *cpart = dataHolder->getCompositePart(cpartId);

    if (cpart == NULL) {
        throw Sb7Exception();
    }
    auto iter=cpart->getUsedIn()->getIter();
    map<int, set<int>> locksRequired;
    vector<BaseAssembly*> bassms;
    while (iter.has_next())
    {
        set<int> lreq;
        auto* ba = (BaseAssembly*) iter.next();
        ILSrv.getLockStack(ba, &lreq);
        locksRequired[ba->getId()] = lreq;
        bassms.push_back(ba);
    }

    sort(bassms.begin(), bassms.end(), [](BaseAssembly* a, BaseAssembly* b) {
        return a->getId() < b->getId();
    });

    for (auto* ca: bassms) {
        ILSrv.IntentionLock(tid,dataHolder, ca, 0, &(locksRequired[ca->getId()]));
    }
    dataHolder->deleteCompositePart(cpart);
    for (auto* ca: bassms) {
        ILSrv.IntentionUnlock(tid,ca, &(locksRequired[ca->getId()]));
    }


    // pthread_rwlock_t *lock = dominatorHelper::getIntentioninatorLock(dataHolder, &(min), &(max));
    // auto *inv = new interval(min, max, 1);
    // if (!domPool.IsOverlap(inv, 1, tid)) {
    //     pthread_rwlock_wrlock(lock);
    //     dataHolder->deleteCompositePart(cpart);
    //     auto *r = new IntentionLockLabeling(dataHolder);
    //     auto t1 = std::chrono::high_resolution_clock::now();
    //     r->traverse(dataHolder->getModule()->getDesignRoot());
    //     auto t2 = std::chrono::high_resolution_clock::now();
    //     domPool.modificationTime = (t2 - t1);
    //     pthread_rwlock_unlock(lock);
    //     domPool.Delete(tid);
    // }
    return 0;
}

/////////////////////////////
// StructuralModification3 //
/////////////////////////////

int sb7::IntentionStructuralModification3::run(int tid) const {
    // generate random composite part id
    int cpartId = get_random()->nextInt(parameters.getMaxCompParts()) + 1;
    CompositePart *cpart = dataHolder->getCompositePart(cpartId);

    if (cpart == NULL) {
        throw Sb7Exception();
    }

    // generate random base assembly id
    int bassmId = get_random()->nextInt(parameters.getMaxBaseAssemblies()) + 1;
    BaseAssembly *bassm = dataHolder->getBaseAssembly(bassmId);

    if (bassm == NULL) {
        throw Sb7Exception();
    }
    set<int> locksRequiredBassm;
    ILSrv.getLockStack(bassm, &locksRequiredBassm);
    set<int> locksRequiredCpart;
    ILSrv.getLockStack(cpart, &locksRequiredCpart);

    ILSrv.IntentionLock(tid,dataHolder, bassm, 1, &locksRequiredBassm);
    ILSrv.IntentionLock(tid,dataHolder, cpart, 1, &locksRequiredCpart);

    bassm->addComponent(cpart);
    ILSrv.IntentionUnlock(tid,bassm, &locksRequiredBassm);
    ILSrv.IntentionUnlock(tid,cpart, &locksRequiredCpart);

//    float min = bassm->m_pre_number;
//    float max = bassm->m_post_number;
//    if (cpart->m_pre_number < min)
//        min = cpart->m_pre_number;
//    if (cpart->m_post_number > max)
//        max = cpart->m_post_number;

    // pthread_rwlock_t *lock = dominatorHelper::getIntentioninatorLock(dataHolder, &(min), &(max));
    // auto *inv = new interval(min, max, 1);
    // if (!domPool.IsOverlap(inv, 1, tid)) {
    //     pthread_rwlock_wrlock(lock);
    //     bassm->addComponent(cpart);
    //     auto *r = new IntentionLockLabeling(dataHolder);
    //     auto t1 = std::chrono::high_resolution_clock::now();
    //     r->traverse(root);
    //     auto t2 = std::chrono::high_resolution_clock::now();
    //     domPool.modificationTime += (t2 - t1);
    //     domPool.count.fetch_add(1);
    //     pthread_rwlock_unlock(lock);
    //     domPool.Delete(tid);
    // }
    return 0;
}
