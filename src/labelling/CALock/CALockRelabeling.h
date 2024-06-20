//
// Created by pandey on 17/06/24.
//

#ifndef STMBENCH_CALOCKRELABELING_H
#define STMBENCH_CALOCKRELABELING_H
#include <utility>

#include "../../data_holder.h"
#include "../../struct/connection.h"
#include "../../struct/assembly.h"
#include "queue"
using namespace sb7;

class CALockRelabeling {
    DataHolder *dataHolder;
    int tid;
public:
    CALockRelabeling(DataHolder
    *
    dh = nullptr,
    int id = -1
    ){
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

    virtual void traverse(CompositePart *component);

    virtual void traverse(AtomicPart *part,
                          Set<AtomicPart *> &setOfVisitedParts, list<int> currLabel);
};


#endif //STMBENCH_CALOCKRELABELING_H
