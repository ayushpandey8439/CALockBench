//
// Created by Ayush Pandey on 30/11/2022.
//

#include "CArelabelling.h"
#include "./struct/connection.h"


using namespace sb7;


void CArelabelling::run() {
    //cout<< "pre-post" << dataHolder->getModule()->getDesignRoot() -> m_pre_number<<" and "<<dataHolder->getModule()->getDesignRoot() -> m_post_number;
    while(!cassmQ.empty()){
        traverse(cassmQ.front());
        cassmQ.pop();
    }
    while(!bassmQ.empty()){
        traverse(bassmQ.front());
        bassmQ.pop();
    }
    while(!cpartQ.empty()){
        traverse(cpartQ.front());
        cpartQ.pop();
    }
    while(!apartQ.empty()){
        Set<AtomicPart *> visitedPartSet;
        traverse(apartQ.front(), visitedPartSet, true);
        apartQ.pop();
    }
}


void CArelabelling::traverse(ComplexAssembly *cassm) {
    list<string> currLabel = cassm->pathLabel;
    list<string> superLabel = cassm->getSuperAssembly()->pathLabel;
    superLabel.push_back("ca"+ to_string(cassm->getId()));

    if(currLabel == superLabel){
        return;
    }

    Set<Assembly *> *subAssm = cassm->getSubAssemblies();
    SetIterator<Assembly *> iter = subAssm->getIter();
    bool childrenAreBase = cassm->areChildrenBaseAssemblies();

    // think about transforming this into a nicer oo design
    while(iter.has_next()) {
        Assembly *assm = iter.next();
        if(!childrenAreBase) {
            cassmQ.push((ComplexAssembly *)assm);
        } else {
            bassmQ.push((BaseAssembly *)assm);
        }
    }
}

void CArelabelling::traverse(BaseAssembly *bassm) {
    list<string> currLabel = bassm->getSuperAssembly()->pathLabel;
    string labelIdentifier = "ba"+ to_string(bassm->getId());
    currLabel.push_back(labelIdentifier);
    bassm->setPathLabel(currLabel);
    BagIterator<CompositePart *> iter = bassm->getComponents()->getIter();
    while(iter.has_next()) {
        CompositePart * cp = iter.next();
        cpartQ.push(cp);
    }
}

void CArelabelling::traverse(CompositePart *cpart) {
    string type = "cp";

    Bag<BaseAssembly *> *usedIn = cpart->getUsedIn();
    BagIterator<BaseAssembly *> biter = usedIn->getIter();
    list<string> firstLabel = biter.next()->pathLabel;

    while(biter.has_next()){
        list<string> common;
        list<string> testLabel = biter.next()->pathLabel;
        set_intersection(firstLabel.begin(), firstLabel.end(), testLabel.begin(),testLabel.end(), back_inserter(common));
        firstLabel = common;
    }

    firstLabel.push_back("cp"+ to_string(cpart->getId()));
    cpart->setPathLabel(firstLabel);

    AtomicPart *rootPart = cpart->getRootPart();
    firstLabel.push_back("ap"+ to_string(rootPart->getId()));
    rootPart->setPathLabel(firstLabel);
    apartQ.push(rootPart);

    //traverse(rootPart, visitedPartSet,true, currPath);
}


void CArelabelling::traverse(AtomicPart *apart, Set<AtomicPart *> &visitedPartSet, bool isRoot) {
    if (isRoot) {
        visitedPartSet.add(apart);
        Set<Connection *> *toConns = apart->getToConnections();
        SetIterator<Connection *> iter = toConns->getIter();
        while (iter.has_next()) {
            Connection *conn = iter.next();
            traverse(conn->getDestination(), visitedPartSet, false);
        }
        visitedPartSet.remove(apart);
    } else if (apart == NULL || visitedPartSet.contains(apart)) {
        return;
    } else {
        visitedPartSet.add(apart);
        string type = "ap";

        Set<Connection *> *fromConns = apart->getFromConnections();
        SetIterator<Connection *> fiter = fromConns->getIter();
        list<string> containerLabel;
        while (containerLabel.empty()) {
            containerLabel = fiter.next()->getSource()->pathLabel;
        }
        while (fiter.has_next()) {
            Connection *conn = fiter.next();
            if (conn->getSource()->hasLabel) {
                list<string> common;
                set_intersection(containerLabel.begin(), containerLabel.end(), conn->getSource()->pathLabel.begin(),conn->getSource()->pathLabel.end(), back_inserter(common));
                containerLabel = common;
            }
        }

        containerLabel.push_back("ap"+ to_string(apart->getId()));
        unordered_set<string> myLabelSet(containerLabel.begin(), containerLabel.end());

        if (myLabelSet != apart->criticalAncestors) {
            apart->setPathLabel(containerLabel);
            // visit all connected parts
            Set<Connection *> *toConns = apart->getToConnections();
            SetIterator<Connection *> iter = toConns->getIter();
            while (iter.has_next()) {
                Connection *conn = iter.next();
                traverse(conn->getDestination(), visitedPartSet, false);
            }
        }
        //visitedPartSet.remove(apart);
    }
}