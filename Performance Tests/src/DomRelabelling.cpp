//
// Created by Ayush Pandey on 30/11/2022.
//

#include "DomRelabelling.h"
#include "./struct/connection.h"
#include "limits.h"

using namespace sb7;

int DomRelabelling::traverse(ComplexAssembly *cassm) const {
    int partsVisited = 0;
//	if(cassm -> m_pre_number == 0)
//	cassm -> m_pre_number = dfscounter++;
//	else dfscounter++;


    Set<Assembly *> *subAssm = cassm->getSubAssemblies();
    SetIterator<Assembly *> iter = subAssm->getIter();
    bool childrenAreBase = cassm->areChildrenBaseAssemblies();

    int pre = INT_MAX, post = 0;

    // think about transforming this into a nicer oo design
    while(iter.has_next()) {
        Assembly *assm = iter.next();

        if(!childrenAreBase) {
            partsVisited += traverse((ComplexAssembly *)assm);

        } else {
            partsVisited += traverse((BaseAssembly *)assm);
        }

        if(assm->m_pre_number < pre)
            pre = assm->m_pre_number;
        if(assm->m_post_number > post)
            post = assm->m_post_number;

    }

    cassm->m_pre_number = pre;
    cassm->m_post_number = post;


    return partsVisited;
}

int DomRelabelling::traverse(BaseAssembly *bassm) const {
    int partsVisited = 0;
//	if(bassm -> m_pre_number == 0)
//	bassm -> m_pre_number = dfscounter++;
//	else dfscounter++;

    SetIterator<CompositePart *> iter = bassm->getComponents()->getIter();

    while(iter.has_next()) {
        partsVisited += traverse(iter.next());
    }
    return partsVisited;
}

int DomRelabelling::traverse(CompositePart *cpart) const {

//	if(cpart -> m_pre_number == 0)
//	cpart -> m_pre_number = dfscounter++;
//	else dfscounter++;


    AtomicPart *rootPart = cpart->getRootPart();
    Set<AtomicPart *> visitedPartSet;



    int retval =  traverse(rootPart, visitedPartSet);

    // Assign intervals to all connected atomic parts
    SetIterator<AtomicPart *> iter	= visitedPartSet.getIter();
    while(iter.has_next()) {
        AtomicPart *ap = iter.next();
        ap->m_pre_number = cpart->m_pre_number;
        ap->m_post_number = cpart->m_post_number;
    }
    return retval;
}

int DomRelabelling::traverse(AtomicPart *apart,
                                    Set<AtomicPart *> &visitedPartSet) const {
    int ret;

    if(apart == NULL) {
        ret = 0;
    } else if(visitedPartSet.contains(apart)) {
        ret = 0;

//		dfscounter++;
    } else {
//		apart -> m_pre_number = dfscounter++;


        ret = performOperationOnAtomicPart(apart, visitedPartSet);
        visitedPartSet.add(apart);

        // visit all connected parts
        Set<Connection *> *toConns = apart->getToConnections();
        SetIterator<Connection *> iter = toConns->getIter();

        while(iter.has_next()) {
            Connection *conn = iter.next();
            ret += traverse(conn->getDestination(), visitedPartSet);
        }
    }
//	apart -> m_post_number = dfscounter++;
    return ret;
}

int DomRelabelling::performOperationOnAtomicPart(AtomicPart *apart,
                                                        Set<AtomicPart *> &visitedPartSet) const {
    apart->nullOperation();
    return 1;
}
