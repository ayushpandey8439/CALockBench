//
// Created by Ayush Pandey on 15/11/2022.
//

#ifndef STMBENCH_TRAVERSAL_OPS_LM_H
#define STMBENCH_TRAVERSAL_OPS_LM_H


#include "../operations.h"
#include "../../containers.h"
#include "../../struct/assembly.h"

namespace sb7 {

    class LMTraversal1 : public Operation {
    protected:
        LMTraversal1(optype t, const char *n, DataHolder *dh)
                : Operation(t, n, dh) {
        }

    public:
        explicit LMTraversal1(DataHolder *dh) : Operation(TRAVERSAL_RO, "T1", dh) {
        }

        int run() const override;

    protected:
        int traverse(ComplexAssembly *complexAssembly) const;

        int traverse(BaseAssembly *baseAssembly) const;

        virtual int traverse(CompositePart *component) const;

        virtual int traverse(AtomicPart *part,
                             Set<AtomicPart *> &setOfVisitedParts) const;

        virtual int performOperationOnAtomicPart(AtomicPart *apart,
                                                 Set<AtomicPart *> &setOfVisitedPartIds) const;
    };

    class LMTraversal2a : public LMTraversal1 {
    public:
        explicit LMTraversal2a(DataHolder *dh) : LMTraversal1(TRAVERSAL, "T2a", dh) {
        }

        int run() const override;

    protected:
        int performOperationOnAtomicPart(AtomicPart *apart,
                                                 Set<AtomicPart *> &setOfVisitedPartIds) const override;
    };

    class LMTraversal2b : public LMTraversal1 {
    public:
        explicit LMTraversal2b(DataHolder *dh) : LMTraversal1(TRAVERSAL, "T2b", dh) {
        }

        int run() const override;

    protected:
        int performOperationOnAtomicPart(AtomicPart *apart,
                                                 Set<AtomicPart *> &setOfVisitedPartIds) const override;
    };

    class LMTraversal2c : public LMTraversal1 {
    public:
        explicit LMTraversal2c(DataHolder *dh) : LMTraversal1(TRAVERSAL, "T2c", dh) {
        }

        int run() const override;

    protected:
        int performOperationOnAtomicPart(AtomicPart *apart,
                                                 Set<AtomicPart *> &setOfVisitedPartIds) const override;
    };

    class LMTraversal3a : public LMTraversal1 {
    protected:
        LMTraversal3a(optype t, const char *n, DataHolder *dh)
                : LMTraversal1(t, n, dh) {
        }

    public:
        explicit LMTraversal3a(DataHolder *dh) : LMTraversal1(TRAVERSAL, "T3a", dh) {
        }

        int run() const override;

    protected:
        int performOperationOnAtomicPart(AtomicPart *apart,
                                                 Set<AtomicPart *> &setOfVisitedPartIds) const override;

        void updateBuildDate(AtomicPart *apart) const;
    };

    class LMTraversal3b : public LMTraversal3a {
    public:
        explicit LMTraversal3b(DataHolder *dh) : LMTraversal3a(TRAVERSAL, "T3b", dh) {
        }

    protected:
        int performOperationOnAtomicPart(AtomicPart *apart,
                                                 Set<AtomicPart *> &setOfVisitedPartIds) const override;
    };

    class LMTraversal3c : public LMTraversal3a {
    public:
        explicit LMTraversal3c(DataHolder *dh) : LMTraversal3a(TRAVERSAL, "T3c", dh) {
        }

    protected:
        int performOperationOnAtomicPart(AtomicPart *apart,
                                                 Set<AtomicPart *> &setOfVisitedPartIds) const override;
    };

    class LMTraversal4 : public LMTraversal1 {
    protected:
        LMTraversal4(optype t, const char *n, DataHolder *dh)
                : LMTraversal1(t, n, dh) {
        }

    public:
        explicit LMTraversal4(DataHolder *dh) : LMTraversal1(TRAVERSAL_RO, "T4", dh) {
        }

        int run() const override;

    protected:
        int traverse(CompositePart *component) const override;

        virtual int traverse(Document *doc) const;

        int traverse(AtomicPart *part,
                             Set<AtomicPart *> &setOfVisitedParts) const override;

        int performOperationOnAtomicPart(AtomicPart *apart,
                                                 Set<AtomicPart *> &setOfVisitedPartIds) const override;
    };

    class LMTraversal5 : public LMTraversal4 {
    public:
        explicit LMTraversal5(DataHolder *dh) : LMTraversal4(TRAVERSAL, "T5", dh) {
        }

        int run() const override;

    protected:
        int traverse(Document *doc) const override;
    };

    class LMTraversal6 : public LMTraversal1 {
    public:
        explicit LMTraversal6(DataHolder *dh) : LMTraversal1(TRAVERSAL_RO, "T6", dh) {
        }

    protected:
        // I made this shorter than in original bench
        int traverse(CompositePart *component) const override;
    };

    // following traversal is actually short traversal, but is here because
    // of it's slightly misleading name
    class LMTraversal7 : public Operation {
    protected:
        LMTraversal7(optype t, const char *n, DataHolder *dh)
                : Operation(t, n, dh) {
        }

    public:
        explicit LMTraversal7(DataHolder *dh)
                : Operation(SHORT_TRAVERSAL_RO, "T7", dh) {
        }

        int run() const override;

    protected:
        int innerRun() const;

        int traverse(CompositePart *cpart) const;

        int traverse(Assembly *assembly,
                     Set<Assembly *> &visitedAssemblies) const;

        virtual void performOperationOnAssembly(Assembly *assembly) const;
    };

    // following two traversals are actually ro operations, but are here
    // because of their slightly misleading names

    class LMTraversal8 : public Operation {
    protected:
        LMTraversal8(optype t, const char *n, DataHolder *dh)
                : Operation(t, n, dh) {
        }

    public:
        explicit LMTraversal8(DataHolder *dh)
                : Operation(OPERATION_RO, "T8", dh) {
        }

        int run() const override;

    protected:
        virtual int traverse(Manual *manual) const;
    };

    class LMTraversal9 : public LMTraversal8 {
    public:
        explicit LMTraversal9(DataHolder *dh)
                : LMTraversal8(OPERATION_RO, "T9", dh) {
        }

    protected:
        int traverse(Manual *manual) const override;
    };

}


#endif //STMBENCH_TRAVERSAL_OPS_LM_H
