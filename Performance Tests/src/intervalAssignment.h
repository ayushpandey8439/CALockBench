//
// Created by Ayush Pandey on 30/11/2022.
//

#ifndef STMBENCH_INTERVALASSIGNMENT_H
#define STMBENCH_INTERVALASSIGNMENT_H

#include "operations/operations.h"
#include "containers.h"
#include "./struct/assembly.h"
#include "queue"

namespace sb7 {
    class DomLockTraversal : public Operation {
    protected:
        DomLockTraversal(optype t, const char *n, DataHolder *dh)
                : Operation(t, n, dh) {
        }

    public:
        DomLockTraversal(DataHolder *dh) : Operation(TRAVERSAL_RO, "T1", dh) {
        }

        virtual int run(int tid) const;

    protected:
        int traverse(ComplexAssembly *complexAssembly) const;
        int traverse(BaseAssembly *baseAssembly) const;
        virtual int traverse(CompositePart *component) const;
        virtual int traverse(AtomicPart *part,
                             Set<AtomicPart *> &setOfVisitedParts) const;
        virtual int performOperationOnAtomicPart(AtomicPart *apart,
                                                 Set<AtomicPart *> &setOfVisitedPartIds) const;
    };
}


#endif //STMBENCH_INTERVALASSIGNMENT_H
