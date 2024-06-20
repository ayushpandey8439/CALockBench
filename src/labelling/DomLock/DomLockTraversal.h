//
// Created by pandey on 17/06/24.
//

#ifndef STMBENCH_DOMLOCKTRAVERSAL_H
#define STMBENCH_DOMLOCKTRAVERSAL_H




#include "queue"
#include "../../operations/operations.h"

namespace sb7 {
    class DomLockLabeling : public Operation {
    protected:
        DomLockLabeling(optype t, const char *n, DataHolder *dh)
                : Operation(t, n, dh) {
        }

    public:
        DomLockLabeling(DataHolder *dh) : Operation(TRAVERSAL_RO, "T1", dh) {
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

#endif //STMBENCH_DOMLOCKTRAVERSAL_H
