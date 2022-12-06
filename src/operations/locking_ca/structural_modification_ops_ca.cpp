//
// Created by Ayush Pandey on 15/11/2022.
//

#include "structural_modification_ops_ca.h"

#include "../../parameters.h"
#include "../../sb7_exception.h"
#include "../../thread/thread.h"
#include "../../lockPool.h"
#include "../../CArelabelling.h"
#include "queue"

extern lockPool pool;

/////////////////////////////
// StructuralModification1 //
/////////////////////////////

int sb7::CAStructuralModification1::run(int tid) const {
    //simple creation of an object does not require relabelling or lock. Only when this component is connected to the hierarchy, we need to label it in order to operate on it.
    dataHolder->createCompositePart();
    return 0;
}

/////////////////////////////
// StructuralModification2 //
/////////////////////////////

int sb7::CAStructuralModification2::run(int tid) const {
    //WriteLockHandle writeLockHandle(CA_lock_srv.getLock());

    // generate random composite part id and try to look it up
    int cpartId = get_random()->nextInt(parameters.getMaxCompParts()) + 1;
    CompositePart *cpart = dataHolder->getCompositePart(cpartId);

    if (cpart == nullptr) {
        throw Sb7Exception();
    }

    Bag<BaseAssembly *> *bassmBag = cpart->getUsedIn();
    BagIterator<BaseAssembly *> iter = bassmBag->getIter();

    auto * l = new lockObject(*cpart, 1);
    if(pool.acquireLock(l, tid)) {
        dataHolder->deleteCompositePart(cpart);
        //Deleting composite parts doesn't require a relabelling because everything inder a composite part if unique and has no links to anything outside the specified composite part.
//        if(cpart->getUsedIn()->size()>0){
//            auto * r = new CArelabelling(dataHolder);
//            r->cpartQ.push(cpart);
//            r->run();
//        }
        pool.releaseLock(l,tid);
    }
    return 0;
}

/////////////////////////////
// StructuralModification3 //
/////////////////////////////

int sb7::CAStructuralModification3::run(int tid) const {
//    //WriteLockHandle writeLockHandle(CA_lock_srv.getLock());
//
//    // generate random composite part id
//    int cpartId = get_random()->nextInt(parameters.getMaxCompParts()) + 1;
//    CompositePart *cpart = dataHolder->getCompositePart(cpartId);
//
//    if (cpart == nullptr) {
//        throw Sb7Exception();
//    }
//
//    // generate random base assembly id
//    int bassmId = get_random()->nextInt(parameters.getMaxBaseAssemblies()) + 1;
//    BaseAssembly *bassm = dataHolder->getBaseAssembly(bassmId);
//
//    if (bassm == nullptr) {
//        throw Sb7Exception();
//    }
//
//    DesignObj* lockRequest = pool.addToLockRequest(dataHolder, bassm,cpart);
//    auto * l = new lockObject(*lockRequest, 1);
//    if(pool.acquireLock(l, tid)) {
//        bassm->addComponent(cpart);
//        auto * r = new CArelabelling(dataHolder);
//        r->cpartQ.push(cpart);
//        r->run();
//        pool.releaseLock(l,tid);
//    }
//
//

    return 0;
}

/////////////////////////////
// StructuralModification4 //
/////////////////////////////

int sb7::CAStructuralModification4::run(int tid) const {
//    //WriteLockHandle writeLockHandle(CA_lock_srv.getLock());
//
//    // generate random base assembly id
//    int bassmId = get_random()->nextInt(parameters.getMaxBaseAssemblies()) + 1;
//    BaseAssembly *bassm = dataHolder->getBaseAssembly(bassmId);
//
//    if (bassm == nullptr) {
//        throw Sb7Exception();
//    }
//
//    // select one of composite parts used in the base assembly
//    Bag<CompositePart *> *cpartBag = bassm->getComponents();
//    int compNum = cpartBag->size();
//
//    if (compNum == 0) {
//        throw Sb7Exception();
//    }
//
//    int nextId = get_random()->nextInt(compNum);
//
//    // find component with that ordinal number
//    BagIterator<CompositePart *> iter = cpartBag->getIter();
//    int i = 0;
//
//    while (iter.has_next()) {
//        CompositePart *cpart = iter.next();
//        if (nextId == i) {
//            DesignObj* lockRequest = pool.addToLockRequest(dataHolder, bassm,cpart);
//            auto * l = new lockObject(*lockRequest, 1);
//            if(pool.acquireLock(l, tid)) {
//                bassm->removeComponent(cpart);
//                //relabelling should only be done if the component is actually connected to anything. If not, we can avoid relabelling.
//                if(cpart->getUsedIn()->size()>0){
//                    auto * r = new CArelabelling(dataHolder);
//                    r->cpartQ.push(cpart);
//                    r->run();
//                }
//                pool.releaseLock(l,tid);
//            }
//            return 0;
//        }
//
//        i++;
//    }
//
//    throw Sb7Exception(
//            "SM4: concurrent modification of BaseAssembly.components!");
return 0;
}

/////////////////////////////
// StructuralModification5 //
/////////////////////////////

int sb7::CAStructuralModification5::run(int tid) const {
//    //WriteLockHandle writeLockHandle(CA_lock_srv.getLock());
//
//    // generate random base assembly id
//    int bassmId = get_random()->nextInt(
//            parameters.getMaxBaseAssemblies()) + 1;
//    BaseAssembly *bassm = dataHolder->getBaseAssembly(bassmId);
//
//    if (bassm == nullptr) {
//        throw Sb7Exception();
//    }
//
//    auto * cassm =  bassm->getSuperAssembly();
//
//    auto * l = new lockObject(*cassm, 1);
//    if(pool.acquireLock(l, tid)) {
//        // create sibling base assembly
//        dataHolder->createBaseAssembly(cassm);
//        auto * r = new CArelabelling(dataHolder);
//        r->bassmQ.push(bassm);
//        r->run();
//        pool.releaseLock(l,tid);
//    }
//


    return 0;
}

/////////////////////////////
// StructuralModification6 //
/////////////////////////////

int sb7::CAStructuralModification6::run(int tid) const {
//   // WriteLockHandle writeLockHandle(CA_lock_srv.getLock());
//
//    // generate random base assembly id
//    int bassmId = get_random()->nextInt(
//            parameters.getMaxBaseAssemblies()) + 1;
//    BaseAssembly *bassm = dataHolder->getBaseAssembly(bassmId);
//
//    if (bassm == nullptr) {
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
//
//    auto * l = new lockObject(*cassm, 1);
//    if(pool.acquireLock(l, tid)) {
//        dataHolder->deleteBaseAssembly(bassm);
//        auto *r = new CArelabelling(dataHolder);
//        r->cassmQ.push(cassm);
//        r->run();
//        pool.releaseLock(l, tid);
//    }
    return 0;
}

/////////////////////////////
// StructuralModification7 //
/////////////////////////////

int sb7::CAStructuralModification7::run(int tid) const {
//    //WriteLockHandle writeLockHandle(CA_lock_srv.getLock());
//
//    // generate random complex assembly id
//    int cassmId = get_random()->nextInt(
//            parameters.getMaxComplexAssemblies()) + 1;
//    ComplexAssembly *cassm = dataHolder->getComplexAssembly(cassmId);
//
//    if (cassm == nullptr) {
//        throw Sb7Exception();
//    }
//
//
//    auto * l = new lockObject(*cassm, 1);
//    if(pool.acquireLock(l, tid)) {
//        // create sub assembly
//        dataHolder->createSubAssembly(cassm, parameters.getNumAssmPerAssm());
//        auto *r = new CArelabelling(dataHolder);
//        r->cassmQ.push(cassm);
//        r->run();
//        pool.releaseLock(l, tid);
//    }
    return 1;
}

/////////////////////////////
// StructuralModification8 //
/////////////////////////////

int sb7::CAStructuralModification8::run(int tid) const {
    //WriteLockHandle writeLockHandle(CA_lock_srv.getLock());

    // generate random complex assembly id
//    int cassmId = get_random()->nextInt(
//            parameters.getMaxComplexAssemblies()) + 1;
//    ComplexAssembly *cassm = dataHolder->getComplexAssembly(cassmId);
//
//    if (cassm == nullptr) {
//        throw Sb7Exception();
//    }
//
//    // get super assembly
//    ComplexAssembly *superAssm = cassm->getSuperAssembly();
//
//    // don't continue if we got root complex assembly
//    if (superAssm == nullptr) {
//        throw Sb7Exception();
//    }
//
//    // check if this would break the tree structure
//    Set<Assembly *> *assmSet = superAssm->getSubAssemblies();
//
//    if (assmSet->size() == 1) {
//        throw Sb7Exception();
//    }
//
//
//    auto * l = new lockObject(*superAssm, 1);
//    if(pool.acquireLock(l, tid)) {
//        // delete selected complex assembly
//        dataHolder->deleteComplexAssembly(cassm);
//        auto *r = new CArelabelling(dataHolder);
//        r->cassmQ.push(superAssm);
//        r->run();
//        pool.releaseLock(l, tid);
//    }
//
//


    return 1;
}
