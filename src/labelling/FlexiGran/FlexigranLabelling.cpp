
#include "FlexigranLabelling.h"
#include "../../struct/connection.h"

using namespace sb7;

long int flexiCounter = 0;


//***************************************************************************************************x

int FlexigranLabelling::run(int tid) const {


    int retval;
    dataHolder->getModule()->getDesignRoot()->m_levelFromRoot = 0; // Setting root's level
    traverse(dataHolder->getModule()->getDesignRoot());
    //cout<< "pre-post" << dataHolder->getModule()->getDesignRoot() -> m_pre_number<<" and "<<dataHolder->getModule()->getDesignRoot() -> m_post_number;

    return retval;
}

int FlexigranLabelling::traverse(ComplexAssembly *cassm) const {
    int partsVisited = 0;
    if (cassm->m_pre_number == 0)
        cassm->m_pre_number = ++flexiCounter;
    else ++flexiCounter;


    Set<Assembly *> *subAssm = cassm->getSubAssemblies();
    SetIterator<Assembly *> iter = subAssm->getIter();
    bool childrenAreBase = cassm->areChildrenBaseAssemblies();
    int myLevel = cassm->m_levelFromRoot;

    // think about transforming this into a nicer oo design
    while (iter.has_next()) {
        Assembly *assm = iter.next();
        assm->m_levelFromRoot = myLevel+1;

        if (!childrenAreBase) {
            partsVisited += traverse((ComplexAssembly *) assm);
        } else {
            partsVisited += traverse((BaseAssembly *) assm);
        }
    }

    cassm->m_post_number = ++flexiCounter;


    return partsVisited;
}

int FlexigranLabelling::traverse(BaseAssembly *bassm) const {
    int partsVisited = 0;
    if (bassm->m_pre_number == 0)
        bassm->m_pre_number = ++flexiCounter;
    else ++flexiCounter;

    BagIterator<CompositePart *> iter = bassm->getComponents()->getIter();
    int myLevel = bassm->m_levelFromRoot;

    while (iter.has_next()) {
        CompositePart* cpart = iter.next();
        cpart->m_levelFromRoot = myLevel+1;
        partsVisited += traverse(cpart);
    }
    bassm->m_post_number = ++flexiCounter;
    return partsVisited;
}

int FlexigranLabelling::traverse(CompositePart *cpart) const {

    if (cpart->m_pre_number == 0)
        cpart->m_pre_number = ++flexiCounter;
    else ++flexiCounter;


    AtomicPart *rootPart = cpart->getRootPart();
    rootPart->m_levelFromRoot = cpart->m_levelFromRoot + 1;
    Set<AtomicPart *> visitedPartSet;


    cpart->m_post_number = ++flexiCounter;

    return traverse(rootPart, visitedPartSet);
}

int FlexigranLabelling::traverse(AtomicPart *apart,
                                   Set<AtomicPart *> &visitedPartSet) const {
    int ret;

    if (apart == NULL) {
        ret = 0;
    } else if (visitedPartSet.contains(apart)) {
        ret = 0;

        ++flexiCounter;
    } else {
        apart->m_pre_number = ++flexiCounter;


        ret = performOperationOnAtomicPart(apart, visitedPartSet);
        visitedPartSet.add(apart);

        // visit all connected parts
        Set<Connection *> *toConns = apart->getToConnections();
        SetIterator<Connection *> iter = toConns->getIter();

        while (iter.has_next()) {
            Connection *conn = iter.next();
            AtomicPart* dest = conn->getDestination();
            dest->m_levelFromRoot = apart->m_levelFromRoot + 1;
            ret += traverse(dest, visitedPartSet);
        }
    }
    apart->m_post_number = ++flexiCounter;
    return ret;
}

int FlexigranLabelling::performOperationOnAtomicPart(AtomicPart *apart,
                                                       Set<AtomicPart *> &visitedPartSet) const {
    apart->nullOperation();
    return 1;
}
