//
// Created by Ayush Pandey on 30/11/2022.
//

#ifndef STMBENCH_DOMRELABELLING_H
#define STMBENCH_DOMRELABELLING_H
#include "operations/operations.h"
#include "containers.h"
#include "./struct/assembly.h"
#include "queue"

using namespace sb7;

class DomRelabelling {
    DataHolder *dataHolder;

public:
    DomRelabelling(DataHolder * dh){
        dataHolder = dh;
    }

    int traverse(ComplexAssembly *complexAssembly) const;
    int traverse(BaseAssembly *baseAssembly) const;
    virtual int traverse(CompositePart *component) const;
    virtual int traverse(AtomicPart *part,
                         Set<AtomicPart *> &setOfVisitedParts) const;
    virtual int performOperationOnAtomicPart(AtomicPart *apart,
                                             Set<AtomicPart *> &setOfVisitedPartIds) const;
};


#endif //STMBENCH_DOMRELABELLING_H
