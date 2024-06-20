//
// Created by pandey on 17/06/24.
//

#include <chrono>
#include "CALockRelabeling.h"
#include "../../operations/CALock/CAPool.h"


extern CAPool caPool;


void CALockRelabeling::run() {
    auto t1 = std::chrono::high_resolution_clock::now();
    //cout<< "pre-post" << dataHolder->getModule()->getDesignRoot() -> m_pre_number<<" and "<<dataHolder->getModule()->getDesignRoot() -> m_post_number;
    while (!cassmQ.empty()) {
        traverse(cassmQ.front());
        cassmQ.pop();
    }
    while (!bassmQ.empty()) {
        traverse(bassmQ.front());
        bassmQ.pop();
    }
    while (!cpartQ.empty()) {
        traverse(cpartQ.front());
        cpartQ.pop();
    }
//    while(!apartQ.empty()){
//        Set<AtomicPart *> visitedPartSet;
//        traverse(apartQ.front(), visitedPartSet, true);
//        apartQ.pop();
//    }
    auto t2 = std::chrono::high_resolution_clock::now();
    caPool.modificationTimeCA += (t2 - t1);
    caPool.count.fetch_add(1);
//    cout<<(t2-t1).count()<<endl;
}


void CALockRelabeling::traverse(ComplexAssembly *cassm) {
    if (cassm->isDeleted) {
        return;
    }
    list<int> currLabel = cassm->pathLabel;
    if (cassm != dataHolder->getModule()->getDesignRoot()) {
        list<int> superLabel = cassm->getSuperAssembly()->pathLabel;
        superLabel.push_back((cassm->getId() * 10) + 1);
        if (currLabel == superLabel) {
            return;
        }
    }


    Set<Assembly *> *subAssm = cassm->getSubAssemblies();
    SetIterator<Assembly *> iter = subAssm->getIter();
    bool childrenAreBase = cassm->areChildrenBaseAssemblies();

    // think about transforming this into a nicer oo design
    while (iter.has_next()) {
        Assembly *assm = iter.next();
        if (!childrenAreBase) {
            cassmQ.push((ComplexAssembly *) assm);
        } else {
            bassmQ.push((BaseAssembly *) assm);
        }
    }
}

void CALockRelabeling::traverse(BaseAssembly *bassm) {
    if (bassm->isDeleted) return;

    list<int> currLabel = bassm->getSuperAssembly()->pathLabel;
    currLabel.push_back((bassm->getId() * 10) + 2);
    if (currLabel == bassm->pathLabel) {
        return;
    }
    bassm->setPathLabel(currLabel);
    BagIterator<CompositePart *> iter = bassm->getComponents()->getIter();
    while (iter.has_next()) {
        CompositePart *cp = iter.next();
        cpartQ.push(cp);
    }
}

void CALockRelabeling::traverse(CompositePart *cpart) {
    string type = "cp";
    if (cpart->isDeleted) return;

    Bag<BaseAssembly *> *usedIn = cpart->getUsedIn();
    BagIterator<BaseAssembly *> biter = usedIn->getIter();
    BaseAssembly *b = biter.next();
    list<int> firstLabel = b->pathLabel;
    set<int> removals{};
    for (int a: firstLabel) {
        bool allContain = true;
        while (biter.has_next()) {
            if (!biter.next()->criticalAncestors.contains(a)) {
                allContain = false;
                break;
            }
        }
        if (!allContain) {
            removals.insert(a);
        }
        biter = usedIn->getIter();
    }

    firstLabel.remove_if([removals](int l) { return removals.contains(l); });

//    while(biter.has_next()){
//        list<int> common;
//        list<int> testLabel = biter.next()->pathLabel;
//        set_intersection(firstLabel.begin(), firstLabel.end(), testLabel.begin(),testLabel.end(), back_inserter(common));
//        firstLabel = common;
//    }

    firstLabel.push_back((cpart->getId() + 10) + 3);
    if (firstLabel == cpart->pathLabel) {
        return;
    }
    cpart->setPathLabel(firstLabel);

    AtomicPart *rootPart = cpart->getRootPart();
    firstLabel.push_back((rootPart->getId() * 10) + 4);
    rootPart->setPathLabel(firstLabel);
    apartQ.push(rootPart);

    Set<AtomicPart *> visitedPartSet;

    traverse(rootPart, visitedPartSet, firstLabel);
}


void CALockRelabeling::traverse(AtomicPart *apart, Set<AtomicPart *> &visitedPartSet, list<int> currLabel) {
    if (apart->isDeleted || apart == NULL || visitedPartSet.contains(apart)) {
        return;
    } else {
        visitedPartSet.add(apart);
        Set<Connection *> *fromConns = apart->getFromConnections();
        SetIterator<Connection *> fiter = fromConns->getIter();
//        boost::container::list<int> containerLabel(10,-1);
        set<int> removals;
        for (int a: currLabel) {
            bool allContain = true;
            while (fiter.has_next()) {
                if (!fiter.next()->getSource()->criticalAncestors.contains(a)) {
                    allContain = false;
                    break;
                }
            }
            if (!allContain) {
                removals.insert(a);
            }
            fiter = fromConns->getIter();
        }
        currLabel.remove_if([removals](int l) { return removals.contains(l); });

//        while (fiter.has_next()) {
//            Connection *conn = fiter.next();
//            list<int> tempLabel = (conn->getSource()->pathLabel);
//            if(!tempLabel.empty()){
//                std::set<int> tempPathSet(tempLabel.begin(), tempLabel.end());
//                auto newEnd = remove_if(currLabel.begin(), currLabel.end(),
//                                        [tempPathSet](int l){return (tempPathSet.find(l) == tempPathSet.end());});
//                currLabel.erase(newEnd, currLabel.end());
//            }
//        }

//        containerLabel.push_back((apart->getId()*10)+4);
//        boost::container::flat_set<int> myLabelSet(currLabel.begin(), currLabel.end());

        if (currLabel != apart->pathLabel) {
            apart->setPathLabel(currLabel);
            // visit all connected parts
            Set<Connection *> *toConns = apart->getToConnections();
            SetIterator<Connection *> iter = toConns->getIter();
            while (iter.has_next()) {
                Connection *conn = iter.next();
                currLabel.push_back((conn->getDestination()->getId() * 10) + 4);
                traverse(conn->getDestination(), visitedPartSet, currLabel);
                currLabel.pop_back();
            }
        }
        visitedPartSet.remove(apart);
    }
}