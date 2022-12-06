
#include "struct/connection.h"
#include "operations/operations.h"
#include "labelAssignmentTraversal.h"
#include "parameters.h"
#include "queue"
#include <string>
#include "map"

using namespace sb7;
//***************************************************************************************************

int sb7::CALockTraversal::run(int tid) const {
    //cout<< "pre-post" << dataHolder->getModule()->getDesignRoot() -> m_pre_number<<" and "<<dataHolder->getModule()->getDesignRoot() -> m_post_number;
    queue<ComplexAssembly *> cassmQ;
    queue<BaseAssembly *> bassmQ;
    queue<CompositePart *> cpartQ;
    queue<AtomicPart *> apartQ;


    ComplexAssembly * root = dataHolder->getModule()->getDesignRoot();

    string labelIdentifier = "ca"+ to_string(root->getId());
    list<string >rootLabel = root->pathLabel;
    rootLabel.push_back(labelIdentifier);
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
    while(!apartQ.empty()){
        Set<AtomicPart *> visitedPartSet;
        traverse(apartQ.front(), visitedPartSet, true);
        apartQ.pop();
    }

    return 0;
}

void sb7::CALockTraversal::traverse(ComplexAssembly *cassm, queue<ComplexAssembly *> *cassmQ, queue<BaseAssembly *> *bassmQ) const {
    list<string> currLabel = cassm->pathLabel;

    Set<Assembly *> *subAssm = cassm->getSubAssemblies();
    SetIterator<Assembly *> iter = subAssm->getIter();
    bool childrenAreBase = cassm->areChildrenBaseAssemblies();

    // think about transforming this into a nicer oo design
    while(iter.has_next()) {
        Assembly *assm = iter.next();
        if(!childrenAreBase) {
            string labelIdentifier = "ca"+ to_string(assm->getId());
            currLabel.push_back(labelIdentifier);
            assm->setPathLabel(currLabel);
            cassmQ->push((ComplexAssembly *)assm);
        } else {
            string labelIdentifier = "ba"+ to_string(assm->getId());
            currLabel.push_back(labelIdentifier);
            assm->setPathLabel(currLabel);
            bassmQ->push((BaseAssembly *)assm);
        }
        currLabel.pop_back();
    }
}

void sb7::CALockTraversal::traverse(BaseAssembly *bassm, queue<CompositePart*> *cpartQ) const {
    BagIterator<CompositePart *> iter = bassm->getComponents()->getIter();
    while(iter.has_next()) {
        CompositePart * cp = iter.next();
        cpartQ->push(cp);
    }
}

void sb7::CALockTraversal::traverse(CompositePart *cpart, queue<AtomicPart*> *apartQ) const {
    string type = "cp";

    Bag<BaseAssembly *> *usedIn = cpart->getUsedIn();
    BagIterator<BaseAssembly *> biter = usedIn->getIter();
    list<string> firstLabel = biter.next()->pathLabel;

    while(biter.has_next()){
        list<string> tempPathLabel = biter.next()->pathLabel;
        std::set<string> tempPathSet(tempPathLabel.begin(), tempPathLabel.end());
        auto newEnd = std::remove_if(firstLabel.begin(), firstLabel.end(), [tempPathSet](string l){return (tempPathSet.find(l) == tempPathSet.end());});
        firstLabel.erase(newEnd, firstLabel.end());
    }

    string labelIdentifier = "cp"+ to_string(cpart->getId());
    firstLabel.push_back(labelIdentifier);
    cpart->setPathLabel(firstLabel);

    AtomicPart *rootPart = cpart->getRootPart();
    firstLabel.push_back("ap"+ to_string(rootPart->getId()));
    rootPart->setPathLabel(firstLabel);
    apartQ->push(rootPart);

    //traverse(rootPart, visitedPartSet,true, currPath);
}


void sb7::CALockTraversal::traverse(AtomicPart *apart, Set<AtomicPart *> &visitedPartSet, bool isRoot) const {
    if(isRoot){
        visitedPartSet.add(apart);
        Set<Connection *> *toConns = apart->getToConnections();
        SetIterator<Connection *> iter = toConns->getIter();
        while(iter.has_next()) {
            Connection *conn = iter.next();
            traverse(conn->getDestination(), visitedPartSet, false);
        }
        visitedPartSet.remove(apart);
    }
    else if(apart == NULL || visitedPartSet.contains(apart)) {
        return;
    } else {
        visitedPartSet.add(apart);
        Set<Connection *> *fromConns = apart->getFromConnections();
        SetIterator<Connection *> fiter = fromConns->getIter();
        list<string> containerLabel;

        while(containerLabel.empty()){
            containerLabel = fiter.next()->getSource()->pathLabel;
        }
        while(fiter.has_next()){
            Connection *conn = fiter.next();
            list<string> parentLabel = conn->getSource()->pathLabel;
            if(!parentLabel.empty()){
                std::set<string> tempPathSet(parentLabel.begin(), parentLabel.end());
                auto newEnd = std::remove_if(containerLabel.begin(), containerLabel.end(), [tempPathSet](string l){return (tempPathSet.find(l) == tempPathSet.end());});
                containerLabel.erase(newEnd, containerLabel.end());
            }
        }

        containerLabel.push_back("ap"+ to_string(apart->getId()));
        list<string> apartLabel = apart->pathLabel;
        std::set<string> myLabelSet(containerLabel.begin(),containerLabel.end());
        std::set<string> originalLabelSet(apartLabel.begin(),apartLabel.end());

        if(myLabelSet != originalLabelSet){
            apart->setPathLabel(containerLabel);
            // visit all connected parts
            Set<Connection *> *toConns = apart->getToConnections();
            SetIterator<Connection *> iter = toConns->getIter();
            while(iter.has_next()) {
                Connection *conn = iter.next();
                traverse(conn->getDestination(), visitedPartSet, false);
            }
        }
        //visitedPartSet.remove(apart);
    }
}