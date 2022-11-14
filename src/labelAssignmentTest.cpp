//
// Created by Ayush Pandey on 11/11/2022.
//

#include "labelAssignmentTest.h"

#include "struct/connection.h"
#include "operations/operations.h"
#include "parameters.h"
#include "queue"
#include <string>

int sb7::CALockLabelTest::run(int tid) const {
    //cout<< "pre-post" << dataHolder->getModule()->getDesignRoot() -> m_pre_number<<" and "<<dataHolder->getModule()->getDesignRoot() -> m_post_number;
    traverse(dataHolder->getModule()->getDesignRoot());
    return 0;
}


void sb7::CALockLabelTest::traverse(ComplexAssembly *cassm) const {

    Set<Assembly *> *subAssm = cassm->getSubAssemblies();
    SetIterator<Assembly *> iter = subAssm->getIter();
    bool childrenAreBase = cassm->areChildrenBaseAssemblies();

    if(cassm->pathLabel.front()!= "ca0" || cassm->pathLabel.back()!= ("ca"+ to_string(cassm->getId()))){
        std::cout << std::endl << "Incorrect Complex Assembly Label: ";
        for (auto i: cassm->pathLabel)
            std::cout << i << ' ';
        std::cout<< std::endl;
    }

    // think about transforming this into a nicer oo design
    while(iter.has_next()) {
        Assembly *assm = iter.next();
        if(!childrenAreBase) {
            traverse((ComplexAssembly *)assm);
        } else {
            traverse((BaseAssembly *)assm);
        }
    }
}

void sb7::CALockLabelTest::traverse(BaseAssembly *bassm) const {


    if(bassm->pathLabel.front() != "ca0"|| bassm->pathLabel.back() != ("ba"+ to_string(bassm->getId()))){

        std::cout << std::endl << "Incorrect Base Assembly Label: ";
        for (auto i: bassm->pathLabel)
            std::cout << i << ' ';
        std::cout<< std::endl;
    }


    BagIterator<CompositePart *> iter = bassm->getComponents()->getIter();

    while(iter.has_next()) {
        traverse(iter.next());
    }
}

void sb7::CALockLabelTest::traverse(CompositePart *cpart) const {
    if(cpart->pathLabel.front() != "ca0" || cpart->pathLabel.back() != ("cp"+ to_string(cpart->getId()))){
        std::cout << std::endl << "Incorrect Composite part Label: ";
        for (auto i: cpart->pathLabel)
            std::cout << i << ' ';
        std::cout<< std::endl;
    }

    AtomicPart *rootPart = cpart->getRootPart();
    Set<AtomicPart *> visitedPartSet;

    traverse(rootPart, visitedPartSet);
}


void sb7::CALockLabelTest::traverse(AtomicPart *apart, Set<AtomicPart *> &visitedPartSet) const {
    if(apart == NULL || visitedPartSet.contains(apart)) {
        return;
    } else {
        if(apart->pathLabel.empty()||apart->pathLabel.front() != "ca0" || apart->pathLabel.back() != ("ap"+ to_string(apart->getId())) ){
            std::cout << std::endl << "Incorrect Atomic part Label: ";
            for (auto i: apart->pathLabel)
                std::cout << i << ' ';
            std::cout<< std::endl;
        }

        visitedPartSet.add(apart);


        // visit all connected parts
        Set<Connection *> *toConns = apart->getToConnections();
        SetIterator<Connection *> iter = toConns->getIter();
        while(iter.has_next()) {
            Connection *conn = iter.next();
            traverse(conn->getDestination(), visitedPartSet);
        }
    }
}
