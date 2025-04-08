//
// Created by pandey on 18/06/24.
//

#ifndef STMBENCH_OUTPUT_H
#define STMBENCH_OUTPUT_H

#include <queue>
#include "../operations/operations.h"

using namespace sb7;

class output : public Operation {
protected:
    output(optype t, const char *n, DataHolder *dh)
            : Operation(t, n, dh) {
    }

public:
    output(DataHolder *dh) : Operation(TRAVERSAL_RO, "T1", dh) {
    }


    virtual int run(int tid) const;

    void
    traverse(ComplexAssembly *complexAssembly, queue<ComplexAssembly *> *cassmQ, std::queue<BaseAssembly *> *bassmQ,
             Set<DesignObj *> *visited, ofstream *graph) const;

    void traverse(BaseAssembly *baseAssembly, queue<CompositePart *> *cpartQ, Set<DesignObj *> *visited,
                  ofstream *graph) const;

    virtual void
    traverse(CompositePart *component, queue<AtomicPart *> *apartQ, Set<DesignObj *> *visited, ofstream *graph) const;

    virtual void traverse(AtomicPart *part, Set<DesignObj *> *visited, ofstream *graph) const;
};


#endif //STMBENCH_OUTPUT_H
