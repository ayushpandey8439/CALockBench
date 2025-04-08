
#ifndef FLEXIGRANLABELLING_H
#define FLEXIGRANLABELLING_H
#include "../../operations/operations.h"


namespace sb7
{
    class FlexigranLabelling : public Operation {
    protected:
        FlexigranLabelling(optype t, const char *n, DataHolder *dh)
            : Operation(t, n, dh) {
        }

    public:
        explicit FlexigranLabelling(DataHolder *dh) : Operation(TRAVERSAL_RO, "T1", dh) {
        }

        virtual int run(int tid) const;
        int traverse(ComplexAssembly *complexAssembly) const;
        int traverse(BaseAssembly *baseAssembly) const;
        virtual int traverse(CompositePart *component) const;
        virtual int traverse(AtomicPart *part,
            Set<AtomicPart *> &setOfVisitedParts) const;
        virtual int performOperationOnAtomicPart(AtomicPart *apart,
            Set<AtomicPart *> &setOfVisitedPartIds) const;
    };
}


#endif //FLEXIGRANLABELLING_H
