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
    boost::container::list<int> firstLabel = b->pathLabel;
    firstLabel.push_back((b->getId()*10)+2);

    while(biter.has_next()){
        boost::container::list<int> common;
        boost::container::list<int> testLabel = biter.next()->pathLabel;
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


void CArelabelling::traverse(AtomicPart *apart, Set<AtomicPart *> &visitedPartSet, boost::container::list<int> currLabel) {
    if(apart->isDeleted || apart == NULL || visitedPartSet.contains(apart)) {
        return;
    } else {
        visitedPartSet.add(apart);
        Set<Connection *> *fromConns = apart->getFromConnections();
        SetIterator<Connection *> fiter = fromConns->getIter();
//        boost::container::list<int> containerLabel = apart->pathLabel;
//        containerLabel.push_back((apart->getId()*10)+4);

        while(fiter.has_next()){
            Connection *conn = fiter.next();
            boost::container::list<int> parentLabel = conn->getSource()->pathLabel;
            if(!parentLabel.empty()){
                std::set<int> tempPathSet(parentLabel.begin(), parentLabel.end());
                auto newEnd = remove_if(currLabel.begin(), currLabel.end(), [tempPathSet](int l){return (tempPathSet.find(l) == tempPathSet.end());});
                currLabel.erase(newEnd, currLabel.end());
            }
        }

//        containerLabel.push_back((apart->getId()*10)+4);
        boost::container::list<int> apartLabel = apart->pathLabel;
        std::set<int> myLabelSet(currLabel.begin(),currLabel.end());
        std::set<int> originalLabelSet(apartLabel.begin(),apartLabel.end());

        if(myLabelSet != originalLabelSet){
            apart->setPathLabel(currLabel);
//            for (auto i: currLabel)
//                std::cout << i << ' ';
//            std::cout<< std::endl;
            // visit all connected parts
            Set<Connection *> *toConns = apart->getToConnections();
            SetIterator<Connection *> iter = toConns->getIter();
            while(iter.has_next()) {
                Connection *conn = iter.next();
                currLabel.push_back((conn->getDestination()->getId()*10)+4);
//                conn->getDestination()->setPathLabel(containerLabel);
                traverse(conn->getDestination(), visitedPartSet, currLabel);
                currLabel.pop_back();
            }
        }
        visitedPartSet.remove(apart);
    }
}
