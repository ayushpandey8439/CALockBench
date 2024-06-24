//
// Created by Ayush Pandey on 24/06/2024.
//

#include "MidLabeling.h"
#include "stack"
#include "../../struct/connection.h"

// Anju ----------- Start ----------
int leafCounter = 0;

int MidTraversalReverseDFS::run(int tid) const {
    int retval = traverse(dataHolder->getModule()->getDesignRoot());
    cout << "\nRoot pre-post from RMid order traversal:  " << dataHolder->getModule()->getDesignRoot()->rlm_pre_number
         << " and " << dataHolder->getModule()->getDesignRoot()->rlm_post_number << endl;
    return 0;
}

int MidTraversalReverseDFS::traverse(ComplexAssembly *cassm) const {
    Set<Assembly *> *subAssm = cassm->getSubAssemblies();
    SetIterator<Assembly *> iter = subAssm->getIter();
    bool childrenAreBase = cassm->areChildrenBaseAssemblies();
    int min = INT_MAX, max = 0;
    stack<Assembly *> myChildren;
    while (iter.has_next())
        myChildren.push(iter.next()); // Adding to stack

    Assembly *currentChild;
    while (!(myChildren.empty())) // stack not empty
    {
        currentChild = myChildren.top(); // Getting the top element
        if (childrenAreBase)
            traverse((BaseAssembly *) currentChild);
        else
            traverse((ComplexAssembly *) currentChild);

        if (currentChild->rlm_pre_number < min)
            min = currentChild->rlm_pre_number;
        if (currentChild->rlm_post_number > max)
            max = currentChild->rlm_post_number;

        myChildren.pop(); // Removing the top element
    }

    cassm->rlm_pre_number = min;
    cassm->rlm_post_number = max;
//		cout << "cassm id " << cassm->getId() << ": (" << min << ", " << max << ")" << "dom : (" << cassm->m_pre_number << ", " << cassm->m_post_number << ")" << endl;
    return 0;
}


int MidTraversalReverseDFS::traverse(BaseAssembly *bassm) const {

//		cout << "In baseAssm code----" << endl;
    stack<CompositePart *> myChildren;
    int min = INT_MAX, max = 0;
    BagIterator<CompositePart *> iter = bassm->getComponents()->getIter();

    while (iter.has_next())
        myChildren.push(iter.next());

    CompositePart *currentChild;
    while (!(myChildren.empty())) // stack not empty
    {
        currentChild = myChildren.top(); // Getting the top element
        traverse((CompositePart *) currentChild);

        if (currentChild->rlm_pre_number < min)
            min = currentChild->rlm_pre_number;
        if (currentChild->rlm_post_number > max)
            max = currentChild->rlm_post_number;

        myChildren.pop(); // Removing the top element
    }
    bassm->rlm_pre_number = min;
    bassm->rlm_post_number = max;

//		cout << "bassm id " << bassm->getId() << ": (" << min << ", " << max << ")"<< "dom : (" << bassm->m_pre_number << ", " << bassm->m_post_number << ")"  << endl;
    return 0;
}


int MidTraversalReverseDFS::traverse(CompositePart *cpart) const {
    if (cpart->rlm_pre_number == 0) {
        leafCounter++;
        cpart->rlm_pre_number = leafCounter;
        cpart->rlm_post_number = leafCounter;
//		cout << "cpart id " << cpart->getId() << ": (" << leafCounter << ", " << leafCounter << ")" << "dom : (" << cpart->m_pre_number << ", " << cpart->m_post_number << ")" << endl;
        // Give the same rlm interval to all the atomic parts below it.
    }

    AtomicPart *rootPart = cpart->getRootPart();
    Set<AtomicPart *> visitedPartSet;
    int retval = traverse(rootPart, visitedPartSet);

    SetIterator<AtomicPart *> iter = visitedPartSet.getIter();
    while (iter.has_next()) {
        AtomicPart *ap = iter.next();
        ap->rlm_pre_number = cpart->rlm_pre_number;
        ap->rlm_post_number = cpart->rlm_post_number;
        //cout << ap->getId() << endl;
    }

    return retval;
}

int MidTraversalReverseDFS::traverse(AtomicPart *apart,
                                          Set<AtomicPart *> &visitedPartSet) const {
    int ret;
    if (apart != NULL && !(visitedPartSet.contains(apart))) {
        visitedPartSet.add(apart);
        // visit all connected parts
        Set<Connection *> *toConns = apart->getToConnections();
        SetIterator<Connection *> iter = toConns->getIter();
        while (iter.has_next()) {
            Connection *conn = iter.next();
            ret += traverse(conn->getDestination(), visitedPartSet);
        }
    }
    return ret;
}


// Anju ----------- End ----------


//***************************************************************************************************

int MidTraversalDFS::run(int tid) const {


    int retval = traverse(dataHolder->getModule()->getDesignRoot());
    cout << "\nRoot pre-post:  " << dataHolder->getModule()->getDesignRoot()->m_pre_number << " and "
         << dataHolder->getModule()->getDesignRoot()->m_post_number << endl;

    return retval;
}

int MidTraversalDFS::traverse(ComplexAssembly *cassm) const {
    int partsVisited = 0;
    Set<Assembly *> *subAssm = cassm->getSubAssemblies();
    SetIterator<Assembly *> iter = subAssm->getIter();
    bool childrenAreBase = cassm->areChildrenBaseAssemblies();

    int pre = INT_MAX, post = 0;

    // think about transforming this into a nicer oo design
    while (iter.has_next()) {
        Assembly *assm = iter.next();

        if (!childrenAreBase) {
            partsVisited += traverse((ComplexAssembly *) assm);

        } else {
            partsVisited += traverse((BaseAssembly *) assm);
        }

        if (assm->m_pre_number < pre)
            pre = assm->m_pre_number;
        if (assm->m_post_number > post)
            post = assm->m_post_number;

    }

    cassm->m_pre_number = pre;
    cassm->m_post_number = post;


    return partsVisited;
}

int MidTraversalDFS::traverse(BaseAssembly *bassm) const {
    int partsVisited = 0;

    BagIterator<CompositePart *> iter = bassm->getComponents()->getIter();

    while (iter.has_next()) {
        partsVisited += traverse(iter.next());
    }
    return partsVisited;
}

int MidTraversalDFS::traverse(CompositePart *cpart) const {

//	if(cpart -> m_pre_number == 0)
//	cpart -> m_pre_number = dfscounter++;
//	else dfscounter++;

    if (cpart->m_pre_number != cpart->m_post_number) {
        cout << cpart->getId() << ": (" << cpart->m_pre_number << ", " << cpart->m_post_number << ")" << endl;
    }

    AtomicPart *rootPart = cpart->getRootPart();
    Set<AtomicPart *> visitedPartSet;


    int retval = traverse(rootPart, visitedPartSet);

    //cout << "Composite part id : " << cpart->getId() << "-------" << endl;
    // Assign intervals to all connected atomic parts
    SetIterator<AtomicPart *> iter = visitedPartSet.getIter();
    while (iter.has_next()) {
        AtomicPart *ap = iter.next();
        ap->m_pre_number = cpart->m_pre_number;
        ap->m_post_number = cpart->m_post_number;
        //cout << ap->getId() << endl;
    }
    //cout << "-------" << endl;
    return retval;
}

int MidTraversalDFS::traverse(AtomicPart *apart,
                                   Set<AtomicPart *> &visitedPartSet) const {
    int ret;

    if (apart == NULL) {
        ret = 0;
    } else if (visitedPartSet.contains(apart)) {
        ret = 0;

    } else {


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
    return ret;
}

int MidTraversalDFS::performOperationOnAtomicPart(AtomicPart *apart,
                                                       Set<AtomicPart *> &visitedPartSet) const {
    apart->nullOperation();
    return 1;
}

