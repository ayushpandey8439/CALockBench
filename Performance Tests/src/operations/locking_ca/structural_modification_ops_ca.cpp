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


/// There are caveats in structural modifications. When we are connecting components then we need to make sure that the
/// Source is actually connected to the graph and the target exists. This can in future be simplified to making sure that
/// simply, both source and target exist. That would mean relabelling of a partial disconnected graph. To achieve this,
/// The nodes need default labels.

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
    // generate random composite part id and try to look it up
    int cpartId = get_random()->nextInt(parameters.getMaxCompParts()) + 1;
    CompositePart *cpart = dataHolder->getCompositePart(cpartId);

    if (cpart == nullptr || cpart->isDeleted) {
        throw Sb7Exception();
    }

    auto *l = new lockObject (cpart->getLabellingId(), &cpart->criticalAncestors, 1);
    pool.acquireLock(l, tid);
    //// Between when the lock was created and the actual deletion happens,
    /// If some other thread races to delete this object, Then, deleting will raise an exception.
    /// We can solve this by taking two stage locks where the first lock is a read lock on the object which
    /// prevents modifications and then we convert the read lock to a write lock.
    if(cpart->hasLabel){
        dataHolder->deleteCompositePart(cpart);
    }
    pool.releaseLock(l,tid);
    return 0;
}

/////////////////////////////
// StructuralModification3 //
/////////////////////////////

int sb7::CAStructuralModification3::run(int tid) const {

    // generate random composite part id
    int cpartId = get_random()->nextInt(parameters.getMaxCompParts()) + 1;
    CompositePart *cpart = dataHolder->getCompositePart(cpartId);

    if (cpart == nullptr || cpart->isDeleted) {
        throw Sb7Exception();
    }

    // generate random base assembly id
    int bassmId = get_random()->nextInt(parameters.getMaxBaseAssemblies()) + 1;
    BaseAssembly *bassm = dataHolder->getBaseAssembly(bassmId);

    if (bassm == nullptr || bassm->isDeleted) {
        throw Sb7Exception();
    }

    list<int> lockLabel = {};

    auto it = cpart->pathLabel.end();
    while(it!=cpart->pathLabel.begin()){
        int val = *it;
        if(bassm->criticalAncestors.contains(val)){
            lockLabel.push_back(*it);
            break;
        }
        --it;
//        if(lscaHelpers::hasCriticalAncestor(&cpart->criticalAncestors, *it)){
//            lockLabel.push_back(*it);
//        }

    }
//    lockLabel= pool.addToLockRequest(dataHolder, bassm->pathLabel,cpart->pathLabel);
//    set_intersection(bassm->pathLabel.begin(), bassm->pathLabel.end(), cpart->pathLabel.begin(), cpart->pathLabel.end(),back_inserter(lockLabel));
    pair<DesignObj*, bool> lo = lscaHelpers::getLockObject(&lockLabel, dataHolder);
    /// When adding a component, it is possible that the composite part we are going to add isn't connected.
    /// This means. a lock on the base assembly is enough.
    if(!lo.second){
        lo.first = bassm;
    }

    auto * l = new lockObject (lo.first->getLabellingId(), &lo.first->criticalAncestors, 1);
    if(pool.acquireLock(l, tid)) {
        /// Similar to SM2, If some thread as deleted the element we are going to modify then we cannot progress with the addition.
        /// This also needs the ability to convert a read lock into a write lock.
        if(bassm->hasLabel && cpart->hasLabel){
            bassm->addComponent(cpart);
            auto t1 = std::chrono::high_resolution_clock::now();
            auto * r = new CArelabelling(dataHolder);
            r->cpartQ.push(cpart);
            r->run();
            auto t2 = std::chrono::high_resolution_clock::now();
            pool.modificationTimeCA+= t2-t1;
        }
        pool.releaseLock(l,tid);
    }



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
//    if (bassm == nullptr || !bassm->hasLabel) {
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
//        /// Delete composite part and iterating over it to make locks is a trouble.
//        /// Should we take read locks?
//        CompositePart *cpart = iter.next();
//        if (nextId == i && cpart->hasLabel && bassm->hasLabel) {
//            list<int> lockRequest = pool.addToLockRequest(dataHolder, bassm->pathLabel,cpart->pathLabel);
//            DesignObj * lo = lscaHelpers::getLockObject(lockRequest, dataHolder);
//            auto *l = new lockObject (lo->getLabellingId(), &lo->criticalAncestors, 1);
//            if(pool.acquireLock(l, tid)) {
//                /// Only issue the delete if the component has not be concurrently disconnected before the lock request was granted.
//                if(bassm->hasLabel && cpart->hasLabel){
//                    bassm->removeComponent(cpart);
//                    //relabelling should only be done if the component is actually connected to anything. If not, we can avoid relabelling.
//                    if(cpart->getUsedIn()->size()>0){
//                        auto * r = new CArelabelling(dataHolder);
//                        r->cpartQ.push(cpart);
//                        r->run();
//                    }
//                }
//                pool.releaseLock(l,tid);
//            }
//            return 0;
//        }
//
//        i++;
//    }

//    throw Sb7Exception(
//            "SM4: concurrent modification of BaseAssembly.components!");
return 0;
}

/////////////////////////////
// StructuralModification5 //
/////////////////////////////

int sb7::CAStructuralModification5::run(int tid) const {
    // generate random base assembly id
    int bassmId = get_random()->nextInt(
            parameters.getMaxBaseAssemblies()) + 1;
    BaseAssembly *bassm = dataHolder->getBaseAssembly(bassmId);

    if (bassm == nullptr || !bassm->hasLabel) {
        throw Sb7Exception();
    }

    auto * cassm =  bassm->getSuperAssembly();

    auto * l = new lockObject (cassm->getLabellingId(), &cassm->criticalAncestors, 1);
    pool.acquireLock(l, tid);
    /// Create sibling base assembly only if both the base and complex assembly exist and the complex assembly has a label.
    if(bassm != nullptr && cassm->hasLabel){
        dataHolder->createBaseAssembly(cassm);
        auto * r = new CArelabelling(dataHolder);
        r->bassmQ.push(bassm);
        r->run();
    }
    pool.releaseLock(l,tid);



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
