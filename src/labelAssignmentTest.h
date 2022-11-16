//
// Created by Ayush Pandey on 11/11/2022.
//

#ifndef SB7_LOCK_LABELASSIGNMENTTEST_H
#define SB7_LOCK_LABELASSIGNMENTTEST_H

#include "struct/connection.h"
#include "operations/operations.h"
#include "parameters.h"
#include "queue"
#include <string>

namespace sb7 {


    class CALockLabelTest : public Operation {
    protected:
        CALockLabelTest(optype t, const char *n, DataHolder *dh)
                : Operation(t, n, dh) {
        }

    public:
        CALockLabelTest(DataHolder *dh) : Operation(TRAVERSAL_RO, "T1", dh) {
        }

        virtual int run(int tid) const;

    protected:
        void traverse(ComplexAssembly *complexAssembly) const;
        void traverse(BaseAssembly *baseAssembly) const;
        virtual void traverse(CompositePart *component) const;
        virtual void traverse(AtomicPart *part,
                              Set<AtomicPart *> &setOfVisitedParts) const;
    };
}

#endif //SB7_LOCK_LABELASSIGNMENTTEST_H
