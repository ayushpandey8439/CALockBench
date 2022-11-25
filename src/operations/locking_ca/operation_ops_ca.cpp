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
    if (!query.found) {
        throw Sb7Exception();
    }

    int ret = 0;

    // if complex assembly was found process it
    ComplexAssembly *cassm = query.val;
    ComplexAssembly *superAssm = cassm->getSuperAssembly();
    auto *l = new lockObject(superAssm, 'r');
    // if this assembly is root perform operation on it
    if (pool.acquireLock(l, tid)) {
        //cout<< "Lock acquired"<<endl;
        pthread_rwlock_rdlock(&cassm->NodeLock);
        performOperationOnComplexAssembly(cassm);
        ret = 1;
        pool.releaseLock(tid);
        pthread_rwlock_unlock(&cassm->NodeLock);
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

    if (!query.found) {
        throw Sb7Exception();
    }
    vector<BaseAssembly *> bassms;
    vector<DesignObj *> lockRequest;

    // process all sibling base assemblies
    ComplexAssembly *superAssm = query.val->getSuperAssembly();
    Set<Assembly *> *siblingSet = superAssm->getSubAssemblies();
    SetIterator<Assembly *> iter = siblingSet->getIter();
    int ret = 0;

    while (iter.has_next()) {
        auto * bassm = (BaseAssembly*) iter.next();
        vector<DesignObj*> testLabel = bassm->getPathLabel();
        if(!testLabel.empty()) {
            bassms.push_back(bassm);
            lockRequest = pool.addToLockRequest(lockRequest, testLabel);
        }

    }

    if(!lockRequest.empty()){
        DesignObj * d = lockRequest.back();
        auto * l = new lockObject(d, 'r');
        //cout<< "Lock Object is not null"<<endl;
        if(pool.acquireLock(l, tid)){
        //cout<< "Lock acquired"<<endl;
        for(BaseAssembly * b: bassms){
            b->nullOperation();
            ret++;
        }
        pool.releaseLock(tid);
    }
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

    vector<CompositePart *> cparts;
    vector<DesignObj *> lockRequest;

    while (iter.has_next()) {
        CompositePart *cpart = iter.next();
        vector<DesignObj*> testLabel = cpart->getPathLabel();
        if(!testLabel.empty()) {
            cparts.push_back(cpart);
            lockRequest = pool.addToLockRequest(lockRequest, testLabel);
        }

    }

    if(!lockRequest.empty()){
        DesignObj * d = lockRequest.back();
        auto *l = new lockObject(d, 'r');
        //cout<< "Lock Object is not null"<<endl;
        if(pool.acquireLock(l,tid)){
        //cout<< "Lock acquired"<<endl;
        for(CompositePart * c: cparts){
            performOperationOnComponent(c);
            ret++;
        }
        pool.releaseLock(tid);
    }
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
