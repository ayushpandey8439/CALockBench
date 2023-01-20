//
// Created by Ayush Pandey on 30/11/2022.
//

#include "CArelabelling.h"
#include "./struct/connection.h"
#include <algorithm>

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
    if(cassm->isDeleted){
        return;
    }
    boost::container::list<int> currLabel = cassm->pathLabel;
    boost::container::list<int> superLabel = cassm->getSuperAssembly()->pathLabel;
    superLabel.push_back((cassm->getId()*10)+1);

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
    if(bassm->isDeleted) return;

    boost::container::list<int> currLabel = bassm->getSuperAssembly()->pathLabel;
    currLabel.push_back((bassm->getId()*10)+1);
    bassm->setPathLabel(currLabel);
    SetIterator<CompositePart *> iter = bassm->getComponents()->getIter();
    while(iter.has_next()) {
        CompositePart * cp = iter.next();
        cpartQ.push(cp);
    }
}

void CArelabelling::traverse(CompositePart *cpart) {
    string type = "cp";
    if(cpart->isDeleted) return;
    Set<BaseAssembly *> *usedIn = cpart->getUsedIn();
    SetIterator<BaseAssembly *> biter = usedIn->getIter();
    boost::container::list<int> firstLabel = biter.next()->pathLabel;

    while(biter.has_next()){
        boost::container::list<int> common;
        boost::container::list<int> testLabel = biter.next()->pathLabel;
        set_intersection(firstLabel.begin(), firstLabel.end(), testLabel.begin(),testLabel.end(), back_inserter(common));
        firstLabel = common;
    }

    firstLabel.push_back((cpart->getId()+10)+3);
    cpart->setPathLabel(firstLabel);

    AtomicPart *rootPart = cpart->getRootPart();
    firstLabel.push_back((rootPart->getId()*10)+4);
    rootPart->setPathLabel(firstLabel);
    apartQ.push(rootPart);

    //traverse(rootPart, visitedPartSet,true, currPath);
}


void CArelabelling::traverse(AtomicPart *apart, Set<AtomicPart *> &visitedPartSet, bool isRoot) {
    if(apart->isDeleted) return;
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

        Set<Connection *> *fromConns = apart->getFromConnections();
        SetIterator<Connection *> fiter = fromConns->getIter();
        boost::container::list<int> containerLabel(10,-1);
        while (containerLabel.empty() && fiter.has_next()) {
            auto s = fiter.next();
            if(s->getSource()->hasLabel)
                containerLabel = s->getSource()->pathLabel;
        }
        while (fiter.has_next()) {
            Connection *conn = fiter.next();
            if (conn->getSource()->hasLabel) {
                boost::container::list<int> common;
                set_intersection(containerLabel.begin(), containerLabel.end(), conn->getSource()->pathLabel.begin(),conn->getSource()->pathLabel.end(), back_inserter(common));
                containerLabel = common;
            }
        }

        containerLabel.push_back((apart->getId()*10)+4);
        boost::container::flat_set<int> myLabelSet(containerLabel.begin(), containerLabel.end());

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
