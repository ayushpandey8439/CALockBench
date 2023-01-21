//
// Created by Ayush Pandey on 30/11/2022.
//

#include "CArelabelling.h"
#include "./struct/connection.h"
#include "lockPool.h"
#include "interval.h"
#include <algorithm>

using namespace sb7;
extern lockPool pool;


void CArelabelling::run() {
    auto t1 = std::chrono::high_resolution_clock::now();
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
//    while(!apartQ.empty()){
//        Set<AtomicPart *> visitedPartSet;
//        traverse(apartQ.front(), visitedPartSet, true);
//        apartQ.pop();
//    }
    auto t2 = std::chrono::high_resolution_clock::now();
    pool.modificationTimeCA+= (t2-t1);
}


void CArelabelling::traverse(ComplexAssembly *cassm) {
    if(cassm->isDeleted){
        return;
    }
    list<int> currLabel = cassm->pathLabel;
    list<int> superLabel = cassm->getSuperAssembly()->pathLabel;
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

    list<int> currLabel = bassm->getSuperAssembly()->pathLabel;
    currLabel.push_back((bassm->getId()*10)+2);
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
    BaseAssembly *b = biter.next();
    list<int> firstLabel = b->pathLabel;
    firstLabel.push_back((b->getId()*10)+2);

    while(biter.has_next()){
        list<int> common;
        list<int> testLabel = biter.next()->pathLabel;
        set_intersection(firstLabel.begin(), firstLabel.end(), testLabel.begin(),testLabel.end(), back_inserter(common));
        firstLabel = common;
    }

    cpart->setPathLabel(firstLabel);

    AtomicPart *rootPart = cpart->getRootPart();
    firstLabel.push_back((cpart->getId()+10)+3);
    firstLabel.push_back((rootPart->getId()*10)+4);
    rootPart->setPathLabel(firstLabel);
    apartQ.push(rootPart);

    Set<AtomicPart *> visitedPartSet;

    traverse(rootPart, visitedPartSet, firstLabel);
}


void CArelabelling::traverse(AtomicPart *apart, Set<AtomicPart *> &visitedPartSet, list<int> currLabel) {
    if(apart->isDeleted || apart == NULL || visitedPartSet.contains(apart)) {
        return;
    } else {
        visitedPartSet.add(apart);
        Set<Connection *> *fromConns = apart->getFromConnections();
        SetIterator<Connection *> fiter = fromConns->getIter();
//        boost::container::list<int> containerLabel(10,-1);

        while (fiter.has_next()) {
            Connection *conn = fiter.next();
            list<int> tempLabel = (conn->getSource()->pathLabel);
            if(!tempLabel.empty()){
                std::set<int> tempPathSet(tempLabel.begin(), tempLabel.end());
                auto newEnd = remove_if(currLabel.begin(), currLabel.end(),
                                        [tempPathSet](int l){return (tempPathSet.find(l) == tempPathSet.end());});
                currLabel.erase(newEnd, currLabel.end());
            }

//            Connection *conn = fiter.next();
//            if (!conn->getSource()->pathLabel.empty()) {
//                for (auto i: currLabel)
//                    std::cout << i << ' ';
//                std::cout<< std::endl;
//
//                for(auto i: currLabel){
//                    if(!conn->getSource()->criticalAncestors.contains(i)){
//                        currLabel.remove(i);
//                    }
//                }
////                boost::container::list<int> common;
////                set_intersection(currLabel.begin(), currLabel.end(), conn->getSource()->pathLabel.begin(),conn->getSource()->pathLabel.end(), back_inserter(common));
////                currLabel = common;
//            }
        }

//        containerLabel.push_back((apart->getId()*10)+4);
//        boost::container::flat_set<int> myLabelSet(currLabel.begin(), currLabel.end());

        if (currLabel != apart->pathLabel) {
            apart->setPathLabel(currLabel);
            // visit all connected parts
            Set<Connection *> *toConns = apart->getToConnections();
            SetIterator<Connection *> iter = toConns->getIter();
            while (iter.has_next()) {
                Connection *conn = iter.next();
                currLabel.push_back((conn->getDestination()->getId()*10)+4);
                traverse(conn->getDestination(), visitedPartSet, currLabel);
                currLabel.pop_back();
            }
        }
        visitedPartSet.remove(apart);
    }
}
