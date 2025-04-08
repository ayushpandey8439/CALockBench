#include "traversal_ops_num.h"

#include "../../struct/module.h"
#include "../../struct/connection.h"
#include "../../sb7_exception.h"
#include "../../parameters.h"
#include "../../thread/thread.h"
#include <stdio.h>
#include<limits.h>
#include <stack>

//long int dfscounter = 0;


////***************************************************************************************************
//////////////////
//// Traversal1 //
//////////////////
//
//int sb7::MidTraversal1::run(int tid) const {
//    ReadLockHandle smLockHandle(lm_lock_srv.getStructureModificationLock());
//    ReadLockHandle apartLockHandle(lm_lock_srv.getAtomicPartLock());
//    int x = traverse(dataHolder->getModule()->getDesignRoot());
//    std::cout << " it is a traversal: " << x;
//    return x;
//}
//
//int sb7::MidTraversal1::traverse(ComplexAssembly *cassm) const {
//    int partsVisited = 0;
//
//    Set<Assembly *> *subAssm = cassm->getSubAssemblies();
//    SetIterator<Assembly *> iter = subAssm->getIter();
//    bool childrenAreBase = cassm->areChildrenBaseAssemblies();
//
//    // think about transforming this into a nicer oo design
//    while (iter.has_next()) {
//        Assembly *assm = iter.next();
//
//        if (!childrenAreBase) {
//            partsVisited += traverse((ComplexAssembly *) assm);
//        } else {
//            partsVisited += traverse((BaseAssembly *) assm);
//        }
//    }
//
//    return partsVisited;
//}
//
//int sb7::MidTraversal1::traverse(BaseAssembly *bassm) const {
//    int partsVisited = 0;
//    BagIterator<CompositePart *> iter = bassm->getComponents()->getIter();
//
//    while (iter.has_next()) {
//        partsVisited += traverse(iter.next());
//    }
//
//    return partsVisited;
//}
//
//int sb7::MidTraversal1::traverse(CompositePart *cpart) const {
//    AtomicPart *rootPart = cpart->getRootPart();
//    Set<AtomicPart *> visitedPartSet;
//    return traverse(rootPart, visitedPartSet);
//}
//
//int sb7::MidTraversal1::traverse(AtomicPart *apart,
//                                 Set<AtomicPart *> &visitedPartSet) const {
//    int ret;
//
//    if (apart == NULL) {
//        ret = 0;
//    } else if (visitedPartSet.contains(apart)) {
//        ret = 0;
//    } else {
//        ret = performOperationOnAtomicPart(apart, visitedPartSet);
//        visitedPartSet.add(apart);
//
//        // visit all connected parts
//        Set<Connection *> *toConns = apart->getToConnections();
//        SetIterator<Connection *> iter = toConns->getIter();
//
//        while (iter.has_next()) {
//            Connection *conn = iter.next();
//            ret += traverse(conn->getDestination(), visitedPartSet);
//        }
//    }
//
//    return ret;
//}
//
//int sb7::MidTraversal1::performOperationOnAtomicPart(AtomicPart *apart,
//                                                     Set<AtomicPart *> &visitedPartSet) const {
//    apart->nullOperation();
//    return 1;
//}
//
///////////////////
//// Traversal2a //
///////////////////
//
//int sb7::MidTraversal2a::run(int tid) const {
//    ReadLockHandle smLockHandle(lm_lock_srv.getStructureModificationLock());
//    WriteLockHandle apartLockHandle(lm_lock_srv.getAtomicPartLock());
//
//    return traverse(dataHolder->getModule()->getDesignRoot());
//}
//
//int sb7::MidTraversal2a::performOperationOnAtomicPart(AtomicPart *apart,
//                                                      Set<AtomicPart *> &visitedPartSet) const {
//    int ret;
//
//    if (visitedPartSet.size() == 0) {
//        apart->swapXY();
//        ret = 1;
//    } else {
//        apart->nullOperation();
//        ret = 1;
//    }
//
//    return ret;
//}
//
///////////////////
//// Traversal2b //
///////////////////
//
//int sb7::MidTraversal2b::run(int tid) const {
//    ReadLockHandle smLockHandle(lm_lock_srv.getStructureModificationLock());
//    WriteLockHandle apartLockHandle(lm_lock_srv.getAtomicPartLock());
//
//    return traverse(dataHolder->getModule()->getDesignRoot());
//}
//
//int sb7::MidTraversal2b::performOperationOnAtomicPart(AtomicPart *apart,
//                                                      Set<AtomicPart *> &visitedPartSet) const {
//    apart->swapXY();
//    return 1;
//}
//
///////////////////
//// Traversal2c //
///////////////////
//
//int sb7::MidTraversal2c::run(int tid) const {
//    ReadLockHandle smLockHandle(lm_lock_srv.getStructureModificationLock());
//    WriteLockHandle apartLockHandle(lm_lock_srv.getAtomicPartLock());
//
//    return traverse(dataHolder->getModule()->getDesignRoot());
//}
//
//int sb7::MidTraversal2c::performOperationOnAtomicPart(AtomicPart *apart,
//                                                      Set<AtomicPart *> &visitedPartSet) const {
//    apart->swapXY();
//    apart->swapXY();
//    apart->swapXY();
//    apart->swapXY();
//
//    return 4;
//}
//
///////////////////
//// Traversal3a //
///////////////////
//
//int sb7::MidTraversal3a::run(int tid) const {
//    ReadLockHandle smLockHandle(lm_lock_srv.getStructureModificationLock());
//    WriteLockHandle apartLockHandle(lm_lock_srv.getAtomicPartLock());
//
//    return traverse(dataHolder->getModule()->getDesignRoot());
//}
//
//int sb7::MidTraversal3a::performOperationOnAtomicPart(AtomicPart *apart,
//                                                      Set<AtomicPart *> &visitedPartSet) const {
//    int ret;
//
//    if (visitedPartSet.size() == 0) {
//        updateBuildDate(apart);
//        ret = 1;
//    } else {
//        apart->nullOperation();
//        ret = 1;
//    }
//
//    return ret;
//}
//
//void sb7::MidTraversal3a::updateBuildDate(AtomicPart *apart) const {
//    dataHolder->removeAtomicPartFromBuildDateIndex(apart);
//    apart->updateBuildDate();
//    dataHolder->addAtomicPartToBuildDateIndex(apart);
//}
//
///////////////////
//// Traversal3b //
///////////////////
//
//int sb7::MidTraversal3b::performOperationOnAtomicPart(AtomicPart *apart,
//                                                      Set<AtomicPart *> &visitedPartSet) const {
//    updateBuildDate(apart);
//    return 1;
//}
//
///////////////////
//// Traversal3c //
///////////////////
//
//int sb7::MidTraversal3c::performOperationOnAtomicPart(AtomicPart *apart,
//                                                      Set<AtomicPart *> &visitedPartSet) const {
//    updateBuildDate(apart);
//    updateBuildDate(apart);
//    updateBuildDate(apart);
//    updateBuildDate(apart);
//    return 4;
//}
//
//////////////////
//// Traversal4 //
//////////////////
//
//int sb7::MidTraversal4::run(int tid) const {
//    ReadLockHandle smLockHandle(lm_lock_srv.getStructureModificationLock());
//    ReadLockHandle docLockHandle(lm_lock_srv.getDocumentLock());
//
//    return MidTraversal1::traverse(dataHolder->getModule()->getDesignRoot());
//}
//
//int sb7::MidTraversal4::traverse(CompositePart *cpart) const {
//    return traverse(cpart->getDocumentation());
//}
//
//int sb7::MidTraversal4::traverse(Document *doc) const {
//    return doc->searchText('I');
//}
//
//int sb7::MidTraversal4::traverse(AtomicPart *part,
//                                 Set<AtomicPart *> &setOfVisitedParts) const {
//    throw Sb7Exception("T4: traverse(AtomicPart, HashSet<AtomicPart>) called!");
//}
//
//int sb7::MidTraversal4::performOperationOnAtomicPart(AtomicPart *apart,
//                                                     Set<AtomicPart *> &setOfVisitedPartIds) const {
//    throw Sb7Exception("T4: performOperationInAtomicPart(..) called!");
//}
//
//////////////////
//// Traversal5 //
//////////////////
//
//int sb7::MidTraversal5::run(int tid) const {
//    ReadLockHandle smLockHandle(lm_lock_srv.getStructureModificationLock());
//    WriteLockHandle docLockHandle(lm_lock_srv.getDocumentLock());
//
//    return MidTraversal1::traverse(
//            dataHolder->getModule()->getDesignRoot());
//}
//
//int sb7::MidTraversal5::traverse(Document *doc) const {
//    int ret;
//
//    if (doc->textBeginsWith("I am")) {
//        ret = doc->replaceText("I am", "This is");
//    } else if (doc->textBeginsWith("This is")) {
//        ret = doc->replaceText("This is", "I am");
//    } else {
//        throw Sb7Exception(
//                ("T5: illegal document text: " + doc->getText()).c_str());
//    }
//
//    if (!ret) {
//        throw Sb7Exception("T5: concurrent modification!");
//    }
//
//    return ret;
//}
//
//////////////////
//// Traversal6 //
//////////////////
//
//int sb7::MidTraversal6::traverse(CompositePart *cpart) const {
//    cpart->getRootPart()->nullOperation();
//    return 1;
//}
//
////////////////////////////////////////////////
//// Traversal 7 - actually a short traversal //
////////////////////////////////////////////////
//
//int sb7::MidTraversal7::run(int tid) const {
//    ReadLockHandle smLockHandle(lm_lock_srv.getStructureModificationLock());
//    ReadLockHandle assemblyLockHandle(
//            lm_lock_srv.getAssemblyLockArray(),
//            lm_lock_srv.getAssemblyLockArraySize());
//
//    return innerRun(tid);
//}
//
//int sb7::MidTraversal7::innerRun(int tid) const {
//    int apartId = get_random()->nextInt(parameters.getMaxAtomicParts()) + 1;
//    Map<int, AtomicPart *> *apartIdx = dataHolder->getAtomicPartIdIndex();
//
//    Map<int, AtomicPart *>::Query query;
//    query.key = apartId;
//    apartIdx->get(query);
//
//    if (!query.found) {
//        throw Sb7Exception();
//    }
//
//    return traverse(query.val->getPartOf());
//}
//
//int sb7::MidTraversal7::traverse(CompositePart *cpart) const {
//    Set<Assembly *> visitedAssemblies;
//    int ret = 0;
//
//    BagIterator<BaseAssembly *> iter = cpart->getUsedIn()->getIter();
//
//    while (iter.has_next()) {
//        ret += traverse(iter.next(), visitedAssemblies);
//    }
//
//    return ret;
//}
//
//int sb7::MidTraversal7::traverse(Assembly *assembly,
//                                 Set<Assembly *> &visitedAssemblies) const {
//    int ret;
//
//    if (assembly == NULL) {
//        ret = 0;
//    } else if (visitedAssemblies.contains(assembly)) {
//        ret = 0;
//    } else {
//        visitedAssemblies.add(assembly);
//        performOperationOnAssembly(assembly);
//        ret = traverse(assembly->getSuperAssembly(), visitedAssemblies) + 1;
//    }
//
//    return ret;
//}
//
//void sb7::MidTraversal7::performOperationOnAssembly(Assembly *assembly) const {
//    assembly->nullOperation();
//}
////
////////////////////////////////////////////
//// Traversal8 - actually a ro operation //
////////////////////////////////////////////
//
//int sb7::MidTraversal8::run(int tid) const {
//    ReadLockHandle smLockHandle(lm_lock_srv.getStructureModificationLock());
//    ReadLockHandle manLockHandle(lm_lock_srv.getManualLock());
//
//    return traverse(dataHolder->getModule()->getManual());
//}
//
//int sb7::MidTraversal8::traverse(Manual *manual) const {
//    return manual->countOccurences('I');
//}

////////////////////////////////////////////
//// Traversal9 - actually a ro operation //
////////////////////////////////////////////
//
//int sb7::MidTraversal9::traverse(Manual *manual) const {
//    return manual->checkFirstLastCharTheSame();
//}
