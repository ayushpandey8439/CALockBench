//
// Created by pandey on 17/06/24.
//

#ifndef STMBENCH_DOMLOCKRELABELING_H
#define STMBENCH_DOMLOCKRELABELING_H

#include "../../operations/operations.h"
#include "../../containers.h"
#include "../../struct/assembly.h"
#include "queue"

using namespace sb7;

class DomLockRelabeling {
    DataHolder *dataHolder;

public:
    DomLockRelabeling(DataHolder
                      *dh) {
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


#endif //STMBENCH_DOMLOCKRELABELING_H
