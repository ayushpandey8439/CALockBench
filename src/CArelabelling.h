//
// Created by Ayush Pandey on 30/11/2022.
//

#ifndef STMBENCH_CARELABELLING_H
#define STMBENCH_CARELABELLING_H
#include <utility>

#include "./data_holder.h"
#include "queue"

using namespace sb7;

class CArelabelling {
    DataHolder *dataHolder;
public:
    CArelabelling(DataHolder * dh = nullptr){
        dataHolder = dh;
    }
    queue<ComplexAssembly *> cassmQ;
    queue<BaseAssembly *> bassmQ;
    queue<CompositePart *> cpartQ;
    queue<AtomicPart *> apartQ;

    void run();

protected:
    void traverse(ComplexAssembly *complexAssembly);
    void traverse(BaseAssembly *baseAssembly);
    virtual void traverse(CompositePart *component );
    virtual void traverse(AtomicPart *part,
                          Set<AtomicPart *> &setOfVisitedParts, bool isRoot);
};


#endif //STMBENCH_CARELABELLING_H
