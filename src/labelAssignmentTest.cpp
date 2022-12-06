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
    list<string> cassmPathLabel = cassm->pathLabel;
    //cout<<"Size: "<< cassmPathLabel.size()<< endl;
    if(cassmPathLabel.front() != "ca0" || cassmPathLabel.back() != "ca"+to_string(cassm->getId())){
        std::cout << std::endl << "Incorrect Complex Assembly Label: ";
        for (auto i: cassmPathLabel)
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
    list<string > bassmPathlabel = bassm->pathLabel;
    //cout<<"Size: "<< bassmPathlabel.size()<< endl;
    if(bassmPathlabel.front() != "ca0" || bassmPathlabel.back() != "ba"+to_string(bassm->getId())){

        std::cout << std::endl << "Incorrect Base Assembly Label: ";
        for (auto i: bassmPathlabel)
            std::cout << i << ' ';
        std::cout<< std::endl;
    }


    BagIterator<CompositePart *> iter = bassm->getComponents()->getIter();

    while(iter.has_next()) {
        traverse(iter.next());
    }
}

void sb7::CALockLabelTest::traverse(CompositePart *cpart) const {
    list<string > cpartPathLabel = cpart->pathLabel;
    //cout<<"Size: "<< cpartPathLabel.size()<< endl;
    if(cpartPathLabel.front()!="ca0" || cpartPathLabel.back() != "cp"+to_string(cpart->getId())){
        std::cout << std::endl << "Incorrect Composite part Label: ";
        for (auto i: cpartPathLabel)
            std::cout << i << ' ';
        std::cout<< std::endl;
    }

    AtomicPart *rootPart = cpart->getRootPart();
    Set<AtomicPart *> visitedPartSet;

    traverse(rootPart, visitedPartSet);
}


void sb7::CALockLabelTest::traverse(AtomicPart *apart, Set<AtomicPart *> &visitedPartSet) const {
    if(visitedPartSet.contains(apart)){
        return;
    }
    else if(apart == NULL) {
        std::cout<< std::endl << "Null atomic part";
        return;
    } else {
        list<string> apartPathLabel = apart->pathLabel;
        //cout<<"Size: "<< apartPathLabel.size()<< endl;
        if(apartPathLabel.empty() ||apartPathLabel.front() != "ca0" || apartPathLabel.back() != "ap"+to_string(apart->getId())){
            std::cout << std::endl << "Incorrect Atomic part Label: ";
            for (auto i: apartPathLabel)
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
