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
    int tid;
public:
    CArelabelling(DataHolder * dh = nullptr, int id = -1){
        dataHolder = dh;
        tid = id;

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
                          Set<AtomicPart *> &setOfVisitedParts,list<int>  currLabel);
};


#endif //STMBENCH_CARELABELLING_H
