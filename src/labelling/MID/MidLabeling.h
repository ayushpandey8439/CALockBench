//
// Created by Ayush Pandey on 24/06/2024.
//

#ifndef SB7_LOCK_MIDLABELING_H
#define SB7_LOCK_MIDLABELING_H
#include "../../operations/operations.h"


// Anju -------- Start --------
using namespace sb7;

class MidTraversalReverseDFS : public Operation {
public:
    MidTraversalReverseDFS(optype t, const char *n, DataHolder *dh)
            : Operation(t, n, dh) {
    }
    MidTraversalReverseDFS(DataHolder *dh) : Operation(TRAVERSAL_RO, "T1", dh) {
    }

    virtual int run(int tid) const;

    int traverse(ComplexAssembly *complexAssembly) const;

    int traverse(BaseAssembly *baseAssembly) const;
    virtual int traverse(CompositePart *component) const;
    virtual int traverse(AtomicPart *part,
                         Set<AtomicPart *> &setOfVisitedParts) const;
/*			virtual int performOperationOnAtomicPart(AtomicPart *apart,
                Set<AtomicPart *> &setOfVisitedPartIds) const; */
};

class MidTraversalDFS : public Operation {
public:
    MidTraversalDFS(optype t, const char *n, DataHolder *dh)
            : Operation(t, n, dh) {
    }


    MidTraversalDFS(DataHolder *dh) : Operation(TRAVERSAL_RO, "T1", dh) {
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




#endif //SB7_LOCK_MIDLABELING_H
