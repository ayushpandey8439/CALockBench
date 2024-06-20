#include "short_traversal_ops_lm.h"
#include "../../sb7_exception.h"
#include "../../struct/connection.h"
#include "lock_srv_lm.h"
#include "../../thread/thread.h"

/////////////////////
// ShortTraversal1 //
/////////////////////

int sb7::LMShortTraversal1::run() const {
    ReadLockHandle smLockHandle(lm_lock_srv.getStructureModificationLock());
    ReadLockHandle apartLockHandle(lm_lock_srv.getAtomicPartLock());

    return traverse(dataHolder->getModule()->getDesignRoot());
}

// TODO do this in a nicer way, somehow
int sb7::LMShortTraversal1::traverse(Assembly *assm) const {
    if (assm->getType() == assembly_type_complex) {
        return traverse((ComplexAssembly *) assm);
    } else {
        return traverse((BaseAssembly *) assm);
    }
}

int sb7::LMShortTraversal1::traverse(ComplexAssembly *cassm) const {
    // choose one sub assembly to traverse
    Set<Assembly *> *subAssm = cassm->getSubAssemblies();
    int subAssembliesNum = subAssm->size();
    int nextAssm = get_random()->nextInt(subAssembliesNum);

    // find chosen assembly
    int i = 0;
    SetIterator<Assembly *> iter = subAssm->getIter();

    while (iter.has_next()) {
        Assembly *subAssm = iter.next();

        if (i == nextAssm) {
            return traverse(subAssm);
        }

        i++;
    }

    // TODO how can this happen?
    throw Sb7Exception(
            "ST1: size of ComplexAssemby.subAssemblies has changed!");
}

int sb7::LMShortTraversal1::traverse(BaseAssembly *bassm) const {
    // choose one component to traverse
    Bag<CompositePart *> *components = bassm->getComponents();
    int componentNum = components->size();

    if (componentNum == 0) {
        throw Sb7Exception("ST1: no components in base assembly");
    }

    int nextComp = get_random()->nextInt(componentNum);

    // find chosen component and traverse it
    int i = 0;
    BagIterator<CompositePart *> iter = components->getIter();

    while (iter.has_next()) {
        CompositePart *cpart = iter.next();

        if (i == nextComp) {
            return traverse(cpart);
        }

        i++;
    }

    // TODO how can this happen?
    throw Sb7Exception("ST1: size of BaseAssembly.components has changed!");
}

int sb7::LMShortTraversal1::traverse(CompositePart *cpart) const {
    // select one atomic part to traverse
    Set<AtomicPart *> *parts = cpart->getParts();
    int atomicPartNum = parts->size();
    int nextPart = get_random()->nextInt(atomicPartNum);

    // find part to traverse and traverse it
    SetIterator<AtomicPart *> iter = parts->getIter();
    int i = 0;

    while (iter.has_next()) {
        AtomicPart *apart = iter.next();

        if (i == nextPart) {
            return traverse(apart);
        }

        i++;
    }

    throw Sb7Exception("ST1: illegal size of CompositePart.parts!");
}

int sb7::LMShortTraversal1::traverse(AtomicPart *apart) const {
    return apart->getX() + apart->getY();
}

/////////////////////
// ShortTraversal2 //
/////////////////////

int sb7::LMShortTraversal2::run() const {
    ReadLockHandle smLockHandle(lm_lock_srv.getStructureModificationLock());
    ReadLockHandle docLockHandle(lm_lock_srv.getDocumentLock());

    return LMShortTraversal1::traverse(
            dataHolder->getModule()->getDesignRoot());
}

int sb7::LMShortTraversal2::traverse(CompositePart *cpart) const {
    return traverse(cpart->getDocumentation());
}

int sb7::LMShortTraversal2::traverse(AtomicPart *apart) const {
    throw Sb7Exception("ST2: unexpected call to traverse(AtomicPart)!");
}

int sb7::LMShortTraversal2::traverse(Document *doc) const {
    return doc->searchText('I');
}

/////////////////////
// ShortTraversal6 //
/////////////////////

int sb7::LMShortTraversal6::run() const {
    ReadLockHandle smLockHandle(lm_lock_srv.getStructureModificationLock());
    WriteLockHandle apartLockHandle(lm_lock_srv.getAtomicPartLock());

    return LMShortTraversal1::traverse(
            dataHolder->getModule()->getDesignRoot());
}

int sb7::LMShortTraversal6::traverse(AtomicPart *apart) const {
    apart->swapXY();
    return LMShortTraversal1::traverse(apart);
}

/////////////////////
// ShortTraversal7 //
/////////////////////

#define DOC_START_STRING_1 "I am"
#define DOC_START_STRING_2 "This is"

int sb7::LMShortTraversal7::run() const {
    ReadLockHandle smLockHandle(lm_lock_srv.getStructureModificationLock());
    WriteLockHandle docLockHandle(lm_lock_srv.getDocumentLock());

    return LMShortTraversal1::traverse(
            dataHolder->getModule()->getDesignRoot());
}

int sb7::LMShortTraversal7::traverse(Document *doc) const {
    int ret;

    if (doc->textBeginsWith(DOC_START_STRING_1)) {
        ret = doc->replaceText(DOC_START_STRING_1, DOC_START_STRING_2);
    } else if (doc->textBeginsWith(DOC_START_STRING_2)) {
        ret = doc->replaceText(DOC_START_STRING_2, DOC_START_STRING_1);
    } else {
        throw Sb7Exception("ST7: unexpected beginning of Document.text!");
    }

    return ret;
}

/////////////////////
// ShortTraversal8 //
/////////////////////

int sb7::LMShortTraversal8::run() const {
    ReadLockHandle smLockHandle(lm_lock_srv.getStructureModificationLock());
    WriteLockHandle assmLockHandle(
            lm_lock_srv.getAssemblyLockArray(),
            lm_lock_srv.getAssemblyLockArraySize());

    return innerRun();
}

void sb7::LMShortTraversal8::performOperationOnAssembly(Assembly *assm) const {
    assm->updateBuildDate();
}

/////////////////////
// ShortTraversal9 //
/////////////////////

int sb7::LMShortTraversal9::traverse(CompositePart *cpart) const {
    Set<AtomicPart *> visitedParts;
    return traverse(cpart->getRootPart(), visitedParts);
}

int sb7::LMShortTraversal9::traverse(AtomicPart *apart,
                                     Set<AtomicPart *> &visitedParts) const {
    int ret;

    if (apart == NULL) {
        ret = 0;
    } else if (visitedParts.contains(apart)) {
        ret = 0;
    } else {
        ret = performOperationOnAtomicPart(apart);
        visitedParts.add(apart);
        Set<Connection *> *connections = apart->getToConnections();
        SetIterator<Connection *> iter = connections->getIter();

        while (iter.has_next()) {
            ret += traverse(iter.next()->getDestination(), visitedParts);
        }
    }

    return ret;
}

int sb7::LMShortTraversal9::traverse(AtomicPart *apart) const {
    throw Sb7Exception("ST9: unexpected call to traverse(AtomicPart)!");
}

int sb7::LMShortTraversal9::performOperationOnAtomicPart(
        AtomicPart *apart) const {
    apart->nullOperation();
    return 1;
}

//////////////////////
// ShortTraversal10 //
// ///////////////////

int sb7::LMShortTraversal10::run() const {
    ReadLockHandle smLockHandle(lm_lock_srv.getStructureModificationLock());
    WriteLockHandle apartLockHandle(lm_lock_srv.getAtomicPartLock());

    return LMShortTraversal1::traverse(
            dataHolder->getModule()->getDesignRoot());
}

int sb7::LMShortTraversal10::performOperationOnAtomicPart(
        AtomicPart *apart) const {
    apart->swapXY();
    return 1;
}
