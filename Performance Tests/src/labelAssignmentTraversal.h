//
// Created by Ayush Pandey on 11/11/2022.
//

#ifndef SB7_LOCK_LABELASSIGNMENTTRAVERSAL_H
#define SB7_LOCK_LABELASSIGNMENTTRAVERSAL_H

#include "operations/operations.h"
#include "containers.h"
#include "queue"

namespace sb7 {
    class CALockTraversal : public Operation {
    protected:
        CALockTraversal(optype t, const char *n, DataHolder *dh)
                : Operation(t, n, dh) {
        }

    public:
        CALockTraversal(DataHolder *dh) : Operation(TRAVERSAL_RO, "T1", dh) {
        }

        virtual int run(int tid) const;

    protected:
        void traverse(ComplexAssembly *complexAssembly, queue<ComplexAssembly *> *cassmQ, std::queue<BaseAssembly *> *bassmQ) const;
        void traverse(BaseAssembly *baseAssembly, queue<CompositePart*> *cpartQ) const;
        virtual void traverse(CompositePart *component,queue<AtomicPart*> *apartQ ) const;
        virtual void traverse(AtomicPart *part,
                              Set<AtomicPart *> &setOfVisitedParts, list<int> currLabel) const;
    };
}


#endif //SB7_LOCK_LABELASSIGNMENTTRAVERSAL_H
