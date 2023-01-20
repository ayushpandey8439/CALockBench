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
    for(int i: cpart->pathLabel){
        if(bassm->criticalAncestors.contains(i)){
            lockLabel.push_back(i);
        }
    }

//    auto it = cpart->pathLabel.rbegin();
//    while(it!=cpart->pathLabel.rend()){
//        int val = *it;
//        if(bassm->criticalAncestors.contains(val)){
//            lockLabel.push_back(*it);
//            break;
//        }
//        ++it;
//    }
//    lockLabel= pool.addToLockRequest(dataHolder, bassm->pathLabel,cpart->pathLabel);
//    set_intersection(bassm->pathLabel.begin(), bassm->pathLabel.end(), cpart->pathLabel.begin(), cpart->pathLabel.end(),back_inserter(lockLabel));
    pair<DesignObj*, bool> lo = lscaHelpers::getLockObject(&lockLabel, dataHolder);
    /// When adding a component, it is possible that the composite part we are going to add isn't connected.
    /// This means. a lock on the base assembly is enough.
    if(!lo.second){
        lo.first = bassm;
    }
    bool executed = false;

    auto * l = new lockObject (lo.first->getLabellingId(), &lo.first->criticalAncestors, 1);
//    cout<<lo.first->getLabellingId()<<endl;
    if(pool.acquireLock(l, tid)) {
        /// Similar to SM2, If some thread as deleted the element we are going to modify then we cannot progress with the addition.
        /// This also needs the ability to convert a read lock into a write lock.
        if(bassm->hasLabel && cpart->hasLabel){
            executed = true;
            bassm->addComponent(cpart);
            auto t1 = std::chrono::high_resolution_clock::now();
            auto * r = new CArelabelling(dataHolder);
            r->cpartQ.push(cpart);
            r->run();
            auto t2 = std::chrono::high_resolution_clock::now();
            pool.modificationTimeCA+= (t2-t1);
        }
        pool.releaseLock(l,tid);
    }

    if(!executed){
        throw Sb7Exception();
    }



    return 0;
}
