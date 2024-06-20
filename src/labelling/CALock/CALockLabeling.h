//
// Created by pandey on 17/06/24.
//

#ifndef STMBENCH_CALOCKLABELING_H
#define STMBENCH_CALOCKLABELING_H

#include "../../operations/operations.h"
#include "queue"

namespace sb7 {
    class CALockLabeling : public Operation {
    protected:
        CALockLabeling(optype t, const char *n, DataHolder *dh)
        : Operation(t, n, dh) {
        }

    public:
        CALockLabeling(DataHolder *dh) : Operation(TRAVERSAL_RO, "T1", dh) {
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


#endif //STMBENCH_CALOCKLABELING_H
