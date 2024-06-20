//
// Created by Ayush Pandey on 15/11/2022.
//

#include "operation_ops_ca.h"
#include "../../thread/thread.h"

#include "../../parameters.h"
#include "../../sb7_exception.h"
#include "./CAPool.h"

extern CAPool pool;
////////////////
// Operation6 //
////////////////

int sb7::CAOperation6::run(int tid) const {
    //ReadLockHandle readLockHandle(CA_lock_srv.getLock());
    return innerRun(tid);
}

int sb7::CAOperation6::innerRun(int tid) const {
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
    if (!query.found || !query.val->hasLabel) {
        throw Sb7Exception();
    }

    int ret = 0;

    // if complex assembly was found process it
    ComplexAssembly *cassm = query.val;
    ComplexAssembly *superAssm = cassm->getSuperAssembly();
    if(superAssm == NULL) {
        auto * l = new lockObject(cassm->getLabellingId(), &cassm->criticalAncestors, 0);
         //if this assembly is root perform operation on it
        if (pool.acquireLock(l, tid)) {
            //cout<< "Lock acquired"<<endl;
            performOperationOnComplexAssembly(cassm);
            ret = 1;
            pool.releaseLock(l,tid);
        }
        ret = 1;
    } else {
        // else perform operation on all it's siblings (including itself)
        Set<Assembly *> *siblingAssms = superAssm->getSubAssemblies();
        SetIterator<Assembly *> iter = siblingAssms->getIter();
        ret = 0;

        auto * l = new lockObject(superAssm->getLabellingId(), &superAssm->criticalAncestors, 0);
        if(pool.acquireLock(l,tid)){
            while (iter.has_next()) {
                auto * bassm = (BaseAssembly*) iter.next();
                if(bassm->hasLabel) {
                    bassm->nullOperation();
                    ret++;
                }
            }
            pool.releaseLock(l,tid);
        }

    }
    return ret;
}

void sb7::CAOperation6::performOperationOnComplexAssembly(
        ComplexAssembly *cassm) const {
    cassm->nullOperation();
}

////////////////
// Operation7 //
////////////////

int sb7::CAOperation7::run(int tid) const {
    //ReadLockHandle readLockHandle(CA_lock_srv.getLock());
    return innerRun(tid);
}

int sb7::CAOperation7::innerRun(int tid) const {
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

    if (!query.found || !query.val->hasLabel) {
        throw Sb7Exception();
    }
    list<BaseAssembly *> bassms;
    DesignObj * lockRequest;

    // process all sibling base assemblies
    ComplexAssembly *superAssm = query.val->getSuperAssembly();
    Set<Assembly *> *siblingSet = superAssm->getSubAssemblies();
    SetIterator<Assembly *> iter = siblingSet->getIter();
    int ret = 0;

    auto * l = new lockObject(superAssm->getLabellingId(), &superAssm->criticalAncestors, 0);
    if(pool.acquireLock(l,tid)){
        while (iter.has_next()) {
            auto * bassm = (BaseAssembly*) iter.next();
            if(bassm->hasLabel) {
                bassm->nullOperation();
                ret++;
            }
        }
        pool.releaseLock(l,tid);
    }
    return ret;
}

void sb7::CAOperation7::performOperationOnBaseAssembly(
        BaseAssembly *bassm) const {
    bassm->nullOperation();
}

////////////////
// Operation8 //
////////////////

////////////////
// Operation9 //
////////////////

int sb7::CAOperation9::run(int tid) const {
    //WriteLockHandle writeLockHandle(CA_lock_srv.getLock());
    return CAQuery1::innerRun(tid);
}

void sb7::CAOperation9::performOperationOnAtomicPart(AtomicPart *apart) const {
    apart->swapXY();
}

////////////////
// Operation10 //
////////////////

int sb7::CAOperation10::run(int tid) const {
    //WriteLockHandle writeLockHandle(CA_lock_srv.getLock());
    return CAQuery2::innerRun(tid);
}

void sb7::CAOperation10::performOperationOnAtomicPart(AtomicPart *apart) const {
    apart->swapXY();
}
