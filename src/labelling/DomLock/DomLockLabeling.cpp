//
// Created by pandey on 17/06/24.
//

#include "DomLockLabeling.h"
#include "../../struct/connection.h"
#include "limits.h"


long int dfscounter = 0;


//***************************************************************************************************

int sb7::DomLockLabeling::run(int tid) const {


    int retval;
    traverse(dataHolder->getModule()->getDesignRoot());
    //cout<< "pre-post" << dataHolder->getModule()->getDesignRoot() -> m_pre_number<<" and "<<dataHolder->getModule()->getDesignRoot() -> m_post_number;

    return retval;
}

int sb7::DomLockLabeling::traverse(ComplexAssembly *cassm) const {
    int partsVisited = 0;
    if (cassm->m_pre_number == 0)
        cassm->m_pre_number = ++dfscounter;
    else ++dfscounter;


    Set<Assembly *> *subAssm = cassm->getSubAssemblies();
    SetIterator<Assembly *> iter = subAssm->getIter();
    bool childrenAreBase = cassm->areChildrenBaseAssemblies();

    // think about transforming this into a nicer oo design
    while (iter.has_next()) {
        Assembly *assm = iter.next();

        if (!childrenAreBase) {
            partsVisited += traverse((ComplexAssembly *) assm);
        } else {
            partsVisited += traverse((BaseAssembly *) assm);
        }
    }

    cassm->m_post_number = ++dfscounter;


    return partsVisited;
}

int sb7::DomLockLabeling::traverse(BaseAssembly *bassm) const {
    int partsVisited = 0;
    if (bassm->m_pre_number == 0)
        bassm->m_pre_number = ++dfscounter;
    else ++dfscounter;

    BagIterator<CompositePart *> iter = bassm->getComponents()->getIter();

    while (iter.has_next()) {
        partsVisited += traverse(iter.next());
    }
    bassm->m_post_number = ++dfscounter;
    return partsVisited;
}

int sb7::DomLockLabeling::traverse(CompositePart *cpart) const {

    if (cpart->m_pre_number == 0)
        cpart->m_pre_number = ++dfscounter;
    else ++dfscounter;


    AtomicPart *rootPart = cpart->getRootPart();
    Set<AtomicPart *> visitedPartSet;


    cpart->m_post_number = ++dfscounter;

    return traverse(rootPart, visitedPartSet);
}

int sb7::DomLockLabeling::traverse(AtomicPart *apart,
                                   Set<AtomicPart *> &visitedPartSet) const {
    int ret;

    if (apart == NULL) {
        ret = 0;
    } else if (visitedPartSet.contains(apart)) {
        ret = 0;

        ++dfscounter;
    } else {
        apart->m_pre_number = ++dfscounter;


        ret = performOperationOnAtomicPart(apart, visitedPartSet);
        visitedPartSet.add(apart);

        // visit all connected parts
        Set<Connection *> *toConns = apart->getToConnections();
        SetIterator<Connection *> iter = toConns->getIter();

        while (iter.has_next()) {
            Connection *conn = iter.next();
            ret += traverse(conn->getDestination(), visitedPartSet);
        }
    }
    apart->m_post_number = ++dfscounter;
    return ret;
}

int sb7::DomLockLabeling::performOperationOnAtomicPart(AtomicPart *apart,
                                                       Set<AtomicPart *> &visitedPartSet) const {
    apart->nullOperation();
    return 1;
}
