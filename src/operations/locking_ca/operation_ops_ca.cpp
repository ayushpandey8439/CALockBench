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

int sb7::CAOperation6::run() const {
    //ReadLockHandle readLockHandle(CA_lock_srv.getLock());
    return innerRun();
}

int sb7::CAOperation6::innerRun() const {
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

    int ret;

    // if complex assembly was found process it
    ComplexAssembly *cassm = query.val;
    ComplexAssembly *superAssm = cassm->getSuperAssembly();

    // if this assembly is root perform operation on it
    if (superAssm == nullptr) {
        xy: if(pool.acquireLock(cassm)){
        //cout<< "Lock acquired"<<endl;
        pthread_rwlock_rdlock(&cassm->NodeLock);
        performOperationOnComplexAssembly(cassm);
        ret = 1;
        pool.releaseLock(cassm);
        pthread_rwlock_unlock(&cassm->NodeLock);
    } else goto xy;

    } else {
        // else perform operation on all it's siblings (including itself)
        Set<Assembly *> *siblingAssms = superAssm->getSubAssemblies();
        SetIterator<Assembly *> iter = siblingAssms->getIter();
        ret = 0;
        list<ComplexAssembly *> cassms;
        list<string> lockRequest;

        while (iter.has_next()) {
            auto* ca = (ComplexAssembly *) iter.next();

            list<string> testLabel = ca->getPathLabel();
            if(!testLabel.empty()) {
                cassms.push_back(ca);
                lockRequest = pool.addToLockRequest(lockRequest, testLabel);
            }

            DesignObj * lockObject = pool.getLockObject(lockRequest.back(), dataHolder);
            if(lockObject != NULL){
                //cout<< "Lock Object is not null"<<endl;
                xyz: if(pool.acquireLock(lockObject)){
                //cout<< "Lock acquired"<<endl;
                pthread_rwlock_rdlock(&lockObject->NodeLock);
                for(ComplexAssembly * c: cassms){
                    performOperationOnComplexAssembly(c);
                    ret++;
                }
                pool.releaseLock(lockObject);
                pthread_rwlock_unlock(&lockObject->NodeLock);
            } else goto xyz;
        }
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

int sb7::CAOperation7::run() const {
    //ReadLockHandle readLockHandle(CA_lock_srv.getLock());
    return innerRun();
}

int sb7::CAOperation7::innerRun() const {
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
    list<BaseAssembly *> bassms;
    list<string> lockRequest;

    // process all sibling base assemblies
    ComplexAssembly *superAssm = query.val->getSuperAssembly();
    Set<Assembly *> *siblingSet = superAssm->getSubAssemblies();
    SetIterator<Assembly *> iter = siblingSet->getIter();
    int ret = 0;

    while (iter.has_next()) {
        auto * bassm = (BaseAssembly*) iter.next();
        list<string> testLabel = bassm->getPathLabel();
        if(!testLabel.empty()) {
            bassms.push_back(bassm);
            lockRequest = pool.addToLockRequest(lockRequest, testLabel);
        }

    }
    DesignObj * lockObject = pool.getLockObject(lockRequest.back(), dataHolder);
    if(lockObject != NULL){
        //cout<< "Lock Object is not null"<<endl;
        xy: if(pool.acquireLock(lockObject)){
        //cout<< "Lock acquired"<<endl;
        pthread_rwlock_rdlock(&lockObject->NodeLock);
        for(BaseAssembly * b: bassms){
            b->nullOperation();
            ret++;
        }
        pool.releaseLock(lockObject);
        pthread_rwlock_unlock(&lockObject->NodeLock);
    } else goto xy;
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

int sb7::CAOperation8::run() const {
    //ReadLockHandle readLockHandle(CA_lock_srv.getLock());
    return innerRun();
}

int sb7::CAOperation8::innerRun() const {
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
    list<string> lockRequest;

    while (iter.has_next()) {
        CompositePart *cpart = iter.next();
        list<string> testLabel = cpart->getPathLabel();
        if(!testLabel.empty()) {
            cparts.push_back(cpart);
            lockRequest = pool.addToLockRequest(lockRequest, testLabel);
        }

    }

    DesignObj * lockObject = pool.getLockObject(lockRequest.back(), dataHolder);
    if(lockObject != NULL){
        //cout<< "Lock Object is not null"<<endl;
        xy: if(pool.acquireLock(lockObject)){
        //cout<< "Lock acquired"<<endl;
        pthread_rwlock_rdlock(&lockObject->NodeLock);
        for(CompositePart * c: cparts){
            performOperationOnComponent(c);
            ret++;
        }
        pool.releaseLock(lockObject);
        pthread_rwlock_unlock(&lockObject->NodeLock);
    } else goto xy;
    }

    return ret;
}

void sb7::CAOperation8::performOperationOnComponent(CompositePart *comp) const {
    comp->nullOperation();
}

////////////////
// Operation9 //
////////////////

int sb7::CAOperation9::run() const {
    //WriteLockHandle writeLockHandle(CA_lock_srv.getLock());
    return CAQuery1::innerRun();
}

void sb7::CAOperation9::performOperationOnAtomicPart(AtomicPart *apart) const {
    xy: if(pool.acquireLock(apart)){
    //cout<< "Lock acquired"<<endl;
    pthread_rwlock_rdlock(&apart->NodeLock);
    apart->swapXY();
    pool.releaseLock(apart);
    pthread_rwlock_unlock(&apart->NodeLock);
} else goto xy;

}

////////////////
// Operation10 //
////////////////

int sb7::CAOperation10::run() const {
    //WriteLockHandle writeLockHandle(CA_lock_srv.getLock());
    return CAQuery2::innerRun();
}

void sb7::CAOperation10::performOperationOnAtomicPart(AtomicPart *apart) const {
    apart->swapXY();
}

/////////////////
// Operation11 //
/////////////////

#define MANUAL_TEXT_START_1 'I'
#define MANUAL_TEXT_START_2 'i'

int sb7::CAOperation11::run() const {
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

int sb7::CAOperation12::run() const {
    //WriteLockHandle writeLockHandle(CA_lock_srv.getLock());
    return CAOperation6::innerRun();
}

void sb7::CAOperation12::performOperationOnComplexAssembly(
        ComplexAssembly *cassm) const {
    cassm->updateBuildDate();
}

/////////////////
// Operation13 //
/////////////////

int sb7::CAOperation13::run() const {
    //WriteLockHandle writeLockHandle(CA_lock_srv.getLock());
    return CAOperation7::innerRun();
}

void sb7::CAOperation13::performOperationOnBaseAssembly(
        BaseAssembly *bassm) const {
    bassm->updateBuildDate();
}

/////////////////
// Operation14 //
/////////////////

int sb7::CAOperation14::run() const {
    //WriteLockHandle writeLockHandle(CA_lock_srv.getLock());
    return CAOperation8::innerRun();
}

void sb7::CAOperation14::performOperationOnComponent(
        CompositePart *cpart) const {
    cpart->updateBuildDate();
}

/////////////////
// Operation15 //
/////////////////

int sb7::CAOperation15::run() const {
    //WriteLockHandle writeLockHandle(CA_lock_srv.getLock());
    return CAQuery1::innerRun();
}

void sb7::CAOperation15::performOperationOnAtomicPart(AtomicPart *apart) const {
    dataHolder->removeAtomicPartFromBuildDateIndex(apart);
    apart->updateBuildDate();
    dataHolder->addAtomicPartToBuildDateIndex(apart);
}
