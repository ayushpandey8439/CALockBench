//
// Created by Ayush Pandey on 15/11/2022.
//

#include "query_ops_ca.h"
#include "../../helpers.h"
#include "../../parameters.h"
#include "../../lockPool.h"
#include "../../sb7_exception.h"

extern lockPool pool;
////////////
// Query1 //
////////////

#define QUERY1_ITER 10


int sb7::CAQuery1::run(int tid) const {
    //ReadLockHandle readLockHandle(CA_lock_srv.getLock());
    return innerRun(tid);
}

int sb7::CAQuery1::innerRun(int tid) const {
    int count = 0;
    int apart = get_random()->nextInt(
            parameters.getMaxAtomicParts()) + 1;
    Map<int, AtomicPart *> *apartInd = dataHolder->getAtomicPartIdIndex();
    Map<int, AtomicPart *>::Query query;
    query.key = apart;
    apartInd->get(query);

    if (query.found && query.val->hasLabel) {
        AtomicPart * a = query.val;
        if(string(name)=="Q1"){
            auto * l = new lockObject(a->getLabellingId(), &a->criticalAncestors, 0);
            pool.acquireLock(l, tid);
            performOperationOnAtomicPart(query.val);
            count++;
            pool.releaseLock(tid);
            delete l;
        }
        else if(string(name) == "OP9"|| string(name) == "OP15") {
            auto * l= new lockObject(a->getLabellingId(), &a->criticalAncestors, 1);
            if(pool.acquireLock(l, tid)) {
                performOperationOnAtomicPart(query.val);
                count++;
                pool.releaseLock(tid);
                delete l;
            }
        }
    } else {
        Sb7Exception();
    }
    return count;
}

void sb7::CAQuery1::performOperationOnAtomicPart(AtomicPart *apart) const {
    apart->nullOperation();
}

////////////
// Query2 //
////////////

sb7::CAQuery2::CAQuery2(DataHolder *dh, optype t, const char *n, int percent)
        : Operation(t, n, dh) {
    maxAtomicDate = parameters.getMaxAtomicDate();
    minAtomicDate = parameters.getMaxAtomicDate() -
                    percent * (parameters.getMaxAtomicDate() -
                               parameters.getMinAtomicDate()) / 100;
}

int sb7::CAQuery2::run(int tid) const {
    return innerRun(tid);
}

int sb7::CAQuery2::innerRun(int tid) const {
    int count = 0;
    Map<int, Set<AtomicPart *> *> *setInd =
            dataHolder->getAtomicPartBuildDateIndex();
    MapIterator<int, Set<AtomicPart *> *> iter =
            setInd->getRange(minAtomicDate, maxAtomicDate);

    while (iter.has_next()) {
        Set<AtomicPart *> *apartSet = iter.next();
        SetIterator<AtomicPart *> apartIter = apartSet->getIter();

        while (apartIter.has_next()) {
            AtomicPart *apart = apartIter.next();
//            if(apart->hasLabel) {
//                auto * l = new lockObject(apart->getLabellingId(), apart->criticalAncestors, 0);
//                if(pool.acquireLock(l,tid)){
//                    performOperationOnAtomicPart(apart);
//                    count++;
//                    pool.releaseLock(l,tid);
//                }
//            }
        }
    }
    return count;
}

void sb7::CAQuery2::performOperationOnAtomicPart(AtomicPart *apart) const {
    apart->nullOperation();
}

////////////
// Query4 //
////////////

#define QUERY4_ITER 100

int sb7::CAQuery4::run(int tid) const {
    //ReadLockHandle readLockHandle(CA_lock_srv.getLock());
    int ret = 0;

    throw Sb7Exception();

    for (int i = 0; i < QUERY4_ITER; i++) {
//        // construct name of documentation for composite part
//        int partId = get_random()->nextInt(parameters.getMaxCompParts()) + 1;
//        // TODO move all these constants to separate header file
//        ITOA(itoa_buf, partId);
//        string title = "Composite Part #" + (string) itoa_buf;
//
//        // search for document with that name
//        Map<string, Document *> *docInd = dataHolder->getDocumentTitleIndex();
//        Map<string, Document *>::Query query;
//        query.key = title;
//        docInd->get(query);
//
//        list<BaseAssembly *> bassms;
//        DesignObj* lockRequest = nullptr;
//
//        if (query.found) {
//            Document *doc = query.val;
//            CompositePart *cpart = doc->getCompositePart();
//            Bag<BaseAssembly *> *usedIn = cpart->getUsedIn();
//            BagIterator<BaseAssembly *> iter = usedIn->getIter();
//
//            while (iter.has_next()) {
//                BaseAssembly *bassm = iter.next();
//                if (bassm->hasLabel) {
//                    bassms.push_back(bassm);
//                    lockRequest = pool.addToLockRequest(dataHolder,lockRequest, bassm);
//                }
//
//            }
//        }
//        if(lockRequest!= nullptr){
//            auto * l = new lockObject(*lockRequest, 0);
//            //cout<< "Lock Object is not null"<<endl;
//            if(pool.acquireLock(l,tid)){
//                //cout<< "Lock acquired"<<endl;
//                for(BaseAssembly * b: bassms){
//                    b->nullOperation();
//                    ret++;
//                }
//                pool.releaseLock(l,tid);
//                //pthread_rwlock_unlock(&lockObject->NodeLock);
//            }
//        }

    }

    return ret;
}

////////////
// Query5 //
////////////

int sb7::CAQuery5::run(int tid) const {
    //ReadLockHandle readLockHandle(CA_lock_srv.getLock());
    int ret = 0;

    Map<int, BaseAssembly *> *bassmInd = dataHolder->getBaseAssemblyIdIndex();
    MapIterator<int, BaseAssembly *> iter = bassmInd->getAll();

    while (iter.has_next()) {
        ret += checkBaseAssembly(iter.next());
    }

    return ret;
}

int sb7::CAQuery5::checkBaseAssembly(BaseAssembly *bassm) {
    int assmBuildDate = bassm->getBuildDate();
    Bag<CompositePart *> *cparts = bassm->getComponents();
    BagIterator<CompositePart *> iter = cparts->getIter();

    while (iter.has_next()) {
        CompositePart *cpart = iter.next();

        if (cpart->getBuildDate() > assmBuildDate) {
            bassm->nullOperation();
            return 1;
        }
    }

    return 0;
}

////////////
// Query6 //
////////////

int sb7::CAQuery6::run(int tid) const {
    //ReadLockHandle readLockHandle(CA_lock_srv.getLock());
    return checkComplexAssembly(dataHolder->getModule()->getDesignRoot());
}

int sb7::CAQuery6::checkAssembly(Assembly *assembly) const {
    if (assembly->getType() == assembly_type_complex) {
        return checkComplexAssembly((ComplexAssembly *) assembly);
    } else {
        return checkBaseAssembly((BaseAssembly *) assembly);
    }
}

int sb7::CAQuery6::checkComplexAssembly(ComplexAssembly *assembly) const {
    int ret = 0;

    Set<Assembly *> *subAssmSet = assembly->getSubAssemblies();
    SetIterator<Assembly *> iter = subAssmSet->getIter();

    while (iter.has_next()) {
        ret += checkAssembly(iter.next());
    }

    if (ret) {
        assembly->nullOperation();
        ret++;
    }

    return ret;
}

////////////
// Query7 //
////////////

int sb7::CAQuery7::run(int tid) const {
    //ReadLockHandle readLockHandle(CA_lock_srv.getLock());
    int ret = 0;

    Map<int, AtomicPart *> *apartInd = dataHolder->getAtomicPartIdIndex();
    MapIterator<int, AtomicPart *> iter = apartInd->getAll();

    while (iter.has_next()) {
        AtomicPart *apart = iter.next();
        apart->nullOperation();
        ret++;
    }

    return ret;
}
