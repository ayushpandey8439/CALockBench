#include "operation_ops_intention.h"

#include "Intention_lock_srv.h"
#include "../../thread/thread.h"

#include "../../parameters.h"
#include "../../sb7_exception.h"

extern Intention_lock_srv ILSrv;


////////////////
// Operation6 //
////////////////

int sb7::IntentionOperation6::run(int tid) const {
    //ReadLockHandle readLockHandle(intention_lock_srv.getLock());
    return innerRun(tid);
}

int sb7::IntentionOperation6::innerRun(int tid) const {
    // Generate one ranintention number that is in range of possible complex assembly
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
    if (superAssm == NULL) {
        set<int> locksRequired;
        ILSrv.getLockStack(cassm, &locksRequired);
        ILSrv.IntentionLock(tid,dataHolder, cassm, 0, &locksRequired);
        ILSrv.IntentionUnlock(tid, cassm, &locksRequired);
        ret = 0;
    } else {
        // else perform operation on all it's siblings (including itself)
        Set<Assembly *> *siblingAssms = superAssm->getSubAssemblies();
        SetIterator<Assembly *> iter = siblingAssms->getIter();
        map<int, set<int>> locksRequired;
        vector<ComplexAssembly*> cassms;
        ret = 0;
        while (iter.has_next())
        {
            set<int> lreq;
            auto* ca = (ComplexAssembly*) iter.next();
            ILSrv.getLockStack(ca, &lreq);
            locksRequired[ca->getId()] = lreq;
            cassms.push_back(ca);
        }

        sort(cassms.begin(), cassms.end(), [](ComplexAssembly* a, ComplexAssembly* b) {
            return a->getId() < b->getId();
        });

        for (auto* ca: cassms) {
            ILSrv.IntentionLock(tid,dataHolder, ca, 0, &(locksRequired[ca->getId()]));
        }
        for (auto* ca: cassms) {
            performOperationOnComplexAssembly(ca);
            ret++;
        }
        for (auto* ca: cassms) {
            ILSrv.IntentionUnlock(tid,ca, &(locksRequired[ca->getId()]));
        }

    }

    return ret;
}

void sb7::IntentionOperation6::performOperationOnComplexAssembly(
        ComplexAssembly *cassm) const {
    cassm->nullOperation();
}

////////////////
// Operation7 //
////////////////

int sb7::IntentionOperation7::run(int tid) const {
    //ReadLockHandle readLockHandle(intention_lock_srv.getLock());
    return innerRun(tid);
}

int sb7::IntentionOperation7::innerRun(int tid) const {
    // Generate one ranintention number that is in range of possible base assembly
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

    if (!query.found) {
        throw Sb7Exception();
    }

    // process all sibling base assemblies
    ComplexAssembly *superAssm = query.val->getSuperAssembly();
    Set<Assembly *> *siblingSet = superAssm->getSubAssemblies();
    SetIterator<Assembly *> iter = siblingSet->getIter();
    int ret = 0;

    map<int, set<int>> locksRequired;
    vector<BaseAssembly*> bassms;
    ret = 0;
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
    for (auto* ca: bassms) {
        performOperationOnBaseAssembly(ca);
        ret++;
    }
    for (auto* ca: bassms) {
        ILSrv.IntentionUnlock(tid,ca, &(locksRequired[ca->getId()]));
    }


    return ret;
}

void sb7::IntentionOperation7::performOperationOnBaseAssembly(
        BaseAssembly *bassm) const {
    bassm->nullOperation();
}

////////////////
// Operation8 //
////////////////

int sb7::IntentionOperation8::run(int tid) const {
    //ReadLockHandle readLockHandle(intention_lock_srv.getLock());
    return innerRun(tid);
}

int sb7::IntentionOperation8::innerRun(int tid) const {
    // Generate one ranintention number that is in range of possible base assembly
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
    long min = 0, max = 0;

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

    // auto *inv = new interval(min, max, 0);
    // if (!intentionPool.IsOverlap(inv, 0, tid)) {
    //     for (auto *cpart: cparts) {
    //         performOperationOnComponent(cpart);
    //         ret++;
    //     }
    //     intentionPool.Delete(tid);
    // }

    return ret;
}

void sb7::IntentionOperation8::performOperationOnComponent(CompositePart *comp) const {
    comp->nullOperation();
}

////////////////
// Operation9 //
////////////////

int sb7::IntentionOperation9::run(int tid) const {
    //WriteLockHandle writeLockHandle(intention_lock_srv.getLock());
    return IntentionQuery1::innerRun(tid);
}

void sb7::IntentionOperation9::performOperationOnAtomicPart(AtomicPart *apart) const {
    apart->swapXY();
}

////////////////
// Operation10 //
////////////////

int sb7::IntentionOperation10::run(int tid) const {
    //WriteLockHandle writeLockHandle(intention_lock_srv.getLock());
    return IntentionQuery2::innerRun(tid);
}

void sb7::IntentionOperation10::performOperationOnAtomicPart(AtomicPart *apart) const {
    apart->swapXY();
}
