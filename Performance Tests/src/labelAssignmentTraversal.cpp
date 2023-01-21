
#include "struct/connection.h"
#include "operations/operations.h"
#include "labelAssignmentTraversal.h"
#include "parameters.h"
#include "queue"
#include <string>
#include "map"
#include <algorithm>

using namespace sb7;
//***************************************************************************************************

int sb7::CALockTraversal::run(int tid) const {
    //cout<< "pre-post" << dataHolder->getModule()->getDesignRoot() -> m_pre_number<<" and "<<dataHolder->getModule()->getDesignRoot() -> m_post_number;
    queue<ComplexAssembly *> cassmQ;
    queue<BaseAssembly *> bassmQ;
    queue<CompositePart *> cpartQ;
    queue<AtomicPart *> apartQ;


    ComplexAssembly * root = dataHolder->getModule()->getDesignRoot();

    list<int>rootLabel = root->pathLabel;
    rootLabel.push_back((root->getId()*10)+1);
    root->setPathLabel(rootLabel);
    cassmQ.push(root);

    while(!cassmQ.empty()){
        traverse(cassmQ.front(), &cassmQ, &bassmQ);
        cassmQ.pop();
    }
    while(!bassmQ.empty()){
        traverse(bassmQ.front(), &cpartQ);
        bassmQ.pop();
    }
    while(!cpartQ.empty()){
        traverse(cpartQ.front(), &apartQ);
        cpartQ.pop();
    }
//    while(!apartQ.empty()){
//        Set<AtomicPart *> visitedPartSet;
//        traverse(apartQ.front(), visitedPartSet, apartQ.front()->pathLabel);
//        apartQ.pop();
//    }

    return 0;
}

void sb7::CALockTraversal::traverse(ComplexAssembly *cassm, queue<ComplexAssembly *> *cassmQ, queue<BaseAssembly *> *bassmQ) const {
    list<int> currLabel = cassm->pathLabel;

    Set<Assembly *> *subAssm = cassm->getSubAssemblies();
    SetIterator<Assembly *> iter = subAssm->getIter();
    bool childrenAreBase = cassm->areChildrenBaseAssemblies();

    // think about transforming this into a nicer oo design
    while(iter.has_next()) {
        Assembly *assm = iter.next();
        if(!childrenAreBase) {
            int labelIdentifier = (assm->getId()*10)+1;
            currLabel.push_back(labelIdentifier);
            assm->setPathLabel(currLabel);
            cassmQ->push((ComplexAssembly *)assm);
        } else {
            int labelIdentifier = (assm->getId()*10)+2;
            currLabel.push_back(labelIdentifier);
            assm->setPathLabel(currLabel);
            bassmQ->push((BaseAssembly *)assm);
        }
        currLabel.pop_back();
    }
}

void sb7::CALockTraversal::traverse(BaseAssembly *bassm, queue<CompositePart*> *cpartQ) const {
    SetIterator<CompositePart *> iter = bassm->getComponents()->getIter();
    while(iter.has_next()) {
        CompositePart * cp = iter.next();
        cpartQ->push(cp);
    }
}

void sb7::CALockTraversal::traverse(CompositePart *cpart, queue<AtomicPart*> *apartQ) const {
    Set<BaseAssembly *> *usedIn = cpart->getUsedIn();
    SetIterator<BaseAssembly *> biter = usedIn->getIter();
    BaseAssembly *b = biter.next();

    list<int> firstLabel = b->pathLabel;
//    firstLabel.push_back((b->getId()*10)+2);

    while(biter.has_next()){
        list<int> tempPathLabel = biter.next()->pathLabel;
        std::set<int> tempPathSet(tempPathLabel.begin(), tempPathLabel.end());
        auto newEnd = remove_if(firstLabel.begin(), firstLabel.end(), [tempPathSet](int l){return (tempPathSet.find(l) == tempPathSet.end());});
        firstLabel.erase(newEnd, firstLabel.end());
    }

    cpart->setPathLabel(firstLabel);

    AtomicPart *rootPart = cpart->getRootPart();
    firstLabel.push_back((cpart->getId()*10)+3);
    firstLabel.push_back((rootPart->getId()*10)+4);
//    rootPart->setPathLabel(firstLabel);
//    apartQ->push(rootPart);

    Set<AtomicPart *> visitedPartSet;
    traverse(rootPart, visitedPartSet, firstLabel);
}


void sb7::CALockTraversal::traverse(AtomicPart *apart, Set<AtomicPart *> &visitedPartSet, list<int> currLabel) const {
    if(apart == NULL || visitedPartSet.contains(apart)) {
        return;
    } else {
        visitedPartSet.add(apart);
        Set<Connection *> *fromConns = apart->getFromConnections();
        SetIterator<Connection *> fiter = fromConns->getIter();
//        boost::container::list<int> containerLabel = apart->pathLabel;
//        containerLabel.push_back((apart->getId()*10)+4);

        while(fiter.has_next()){
            Connection *conn = fiter.next();
            list<int> parentLabel = conn->getSource()->pathLabel;
            if(!parentLabel.empty()){
                std::set<int> tempPathSet(parentLabel.begin(), parentLabel.end());
                auto newEnd = remove_if(currLabel.begin(), currLabel.end(), [tempPathSet](int l){return (tempPathSet.find(l) == tempPathSet.end());});
                currLabel.erase(newEnd, currLabel.end());
            }
        }

//        containerLabel.push_back((apart->getId()*10)+4);
        list<int> apartLabel = apart->pathLabel;
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
