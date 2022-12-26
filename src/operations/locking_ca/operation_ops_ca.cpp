//
// Created by Ayush Pandey on 15/11/2022.
//

#include "operation_ops_ca.h"
#include "../../thread/thread.h"

#include "../../parameters.h"
#include "../../sb7_exception.h"
#include "../../lockPool.h"

extern lockPool pool;
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

int sb7::CAOperation8::run(int tid) const {
    //ReadLockHandle readLockHandle(CA_lock_srv.getLock());
    return innerRun(tid);
}

int sb7::CAOperation8::innerRun(int tid) const {
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
    list<int> lockRequest;

    while (iter.has_next()) {
        CompositePart *cpart = iter.next();
        if(cpart->hasLabel){
            if(lockRequest.size()!=1){
                if(lockRequest.empty()) lockRequest = cpart->pathLabel;
                else {
                    auto it = lockRequest.begin();
                    auto end = lockRequest.end();
                    while(it != end){
                        if(!lscaHelpers::hasCriticalAncestor(&cpart->criticalAncestors, *it)){
                            it = lockRequest.erase(it);
                        } else {
                            ++it;
                        }
                    }
                }
            }
            cparts.push_back(cpart);
            //lockRequest = pool.addToLockRequest(dataHolder, lockRequest, cpart->pathLabel);
        }
    }

    if(lockRequest.empty()){
        throw Sb7Exception();
    }
    DesignObj* d = lscaHelpers::getLockObject(lockRequest, dataHolder);

    auto * l = new lockObject(d->getLabellingId(), &d->criticalAncestors, 0);
    //cout<< "Lock Object is not null"<<endl;
    if(pool.acquireLock(l,tid)){
        //cout<< "Lock acquired"<<endl;
        for(CompositePart * c: cparts){
            performOperationOnComponent(c);
            ret++;
        }
        pool.releaseLock(l,tid);
    }


    return ret;
}

void sb7::CAOperation8::performOperationOnComponent(CompositePart *comp) const {
    comp->nullOperation();
}

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

/////////////////
// Operation11 //
/////////////////

#define MANUAL_TEXT_START_1 'I'
#define MANUAL_TEXT_START_2 'i'

int sb7::CAOperation11::run(int tid) const {
    //WriteLockHandle writeLockHandle(CA_lock_srv.getLock());
    return CATraversal8::traverse(dataHolder->getModule()->getManual());
}

int sb7::CAOperation11::traverse(Manual *manual) const {
    int ret;

    if (manual->startsWith(MANUAL_TEXT_START_1)) {
        ret = manual->replaceChar(MANUAL_TEXT_START_1, MANUAL_TEXT_START_2);
    } else if (manual->startsWith(MANUAL_TEXT_START_2)) {
        ret = manual->replaceChar(MANUAL_TEXT_START_2, MANUAL_TEXT_START_1);
    } else {
        throw Sb7Exception("OP11: unexpected Manual.text!");
    }

    return ret;
}

/////////////////
// Operation12 //
/////////////////

int sb7::CAOperation12::run(int tid) const {
    //WriteLockHandle writeLockHandle(CA_lock_srv.getLock());
    return CAOperation6::innerRun(tid);
}

void sb7::CAOperation12::performOperationOnComplexAssembly(
        ComplexAssembly *cassm) const {
    cassm->updateBuildDate();
}

/////////////////
// Operation13 //
/////////////////

int sb7::CAOperation13::run(int tid) const {
    //WriteLockHandle writeLockHandle(CA_lock_srv.getLock());
    return CAOperation7::innerRun(tid);
}

void sb7::CAOperation13::performOperationOnBaseAssembly(
        BaseAssembly *bassm) const {
    bassm->updateBuildDate();
}

/////////////////
// Operation14 //
/////////////////

int sb7::CAOperation14::run(int tid) const {
    //WriteLockHandle writeLockHandle(CA_lock_srv.getLock());
    return CAOperation8::innerRun(tid);
}

void sb7::CAOperation14::performOperationOnComponent(
        CompositePart *cpart) const {
    cpart->updateBuildDate();
}

/////////////////
// Operation15 //
/////////////////

int sb7::CAOperation15::run(int tid) const {
    //WriteLockHandle writeLockHandle(CA_lock_srv.getLock());
    return CAQuery1::innerRun(tid);
}

void sb7::CAOperation15::performOperationOnAtomicPart(AtomicPart *apart) const {
    dataHolder->removeAtomicPartFromBuildDateIndex(apart);
    apart->updateBuildDate();
    dataHolder->addAtomicPartToBuildDateIndex(apart);
}
