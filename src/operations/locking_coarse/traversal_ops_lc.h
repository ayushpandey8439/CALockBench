//
// Created by Ayush Pandey on 15/11/2022.
//

#ifndef STMBENCH_TRAVERSAL_OPS_LC_H
#define STMBENCH_TRAVERSAL_OPS_LC_H


#include "../operations.h"
#include "../../containers.h"
#include "../../struct/assembly.h"

namespace sb7 {

    class LCTraversal1 : public Operation {
    protected:
        LCTraversal1(optype t, const char *n, DataHolder *dh)
                : Operation(t, n, dh) {
        }

    public:
        explicit LCTraversal1(DataHolder *dh) : Operation(TRAVERSAL_RO, "T1", dh) {
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

    class LCTraversal2a : public LCTraversal1 {
    public:
        explicit LCTraversal2a(DataHolder *dh) : LCTraversal1(TRAVERSAL, "T2a", dh) {
        }

        int run() const override;

    protected:
        int performOperationOnAtomicPart(AtomicPart *apart,
                                                 Set<AtomicPart *> &setOfVisitedPartIds) const override;
    };

    class LCTraversal2b : public LCTraversal1 {
    public:
        explicit LCTraversal2b(DataHolder *dh) : LCTraversal1(TRAVERSAL, "T2b", dh) {
        }

        int run() const override;

    protected:
        int performOperationOnAtomicPart(AtomicPart *apart,
                                                 Set<AtomicPart *> &setOfVisitedPartIds) const override;
    };

    class LCTraversal2c : public LCTraversal1 {
    public:
        explicit LCTraversal2c(DataHolder *dh) : LCTraversal1(TRAVERSAL, "T2c", dh) {
        }

        int run() const override;

    protected:
        int performOperationOnAtomicPart(AtomicPart *apart,
                                                 Set<AtomicPart *> &setOfVisitedPartIds) const override;
    };

    class LCTraversal3a : public LCTraversal1 {
    protected:
        LCTraversal3a(optype t, const char *n, DataHolder *dh)
                : LCTraversal1(t, n, dh) {
        }

    public:
        explicit LCTraversal3a(DataHolder *dh) : LCTraversal1(TRAVERSAL, "T3a", dh) {
        }

        int run() const override;

    protected:
        int performOperationOnAtomicPart(AtomicPart *apart,
                                                 Set<AtomicPart *> &setOfVisitedPartIds) const override;

        void updateBuildDate(AtomicPart *apart) const;
    };

    class LCTraversal3b : public LCTraversal3a {
    public:
        explicit LCTraversal3b(DataHolder *dh) : LCTraversal3a(TRAVERSAL, "T3b", dh) {
        }

    protected:
        int performOperationOnAtomicPart(AtomicPart *apart,
                                                 Set<AtomicPart *> &setOfVisitedPartIds) const override;
    };

    class LCTraversal3c : public LCTraversal3a {
    public:
        explicit LCTraversal3c(DataHolder *dh) : LCTraversal3a(TRAVERSAL, "T3c", dh) {
        }

    protected:
        int performOperationOnAtomicPart(AtomicPart *apart,
                                                 Set<AtomicPart *> &setOfVisitedPartIds) const override;
    };

    class LCTraversal4 : public LCTraversal1 {
    protected:
        LCTraversal4(optype t, const char *n, DataHolder *dh)
                : LCTraversal1(t, n, dh) {
        }

    public:
        explicit LCTraversal4(DataHolder *dh) : LCTraversal1(TRAVERSAL_RO, "T4", dh) {
        }

    protected:
        int traverse(CompositePart *component) const override;

        virtual int traverse(Document *doc) const;

        int traverse(AtomicPart *part,
                             Set<AtomicPart *> &setOfVisitedParts) const override;

        int performOperationOnAtomicPart(AtomicPart *apart,
                                                 Set<AtomicPart *> &setOfVisitedPartIds) const override;
    };

    class LCTraversal5 : public LCTraversal4 {
    public:
        explicit LCTraversal5(DataHolder *dh) : LCTraversal4(TRAVERSAL, "T5", dh) {
        }

        int run() const override;

    protected:
        int traverse(Document *doc) const override;
    };

    class LCTraversal6 : public LCTraversal1 {
    public:
        explicit LCTraversal6(DataHolder *dh) : LCTraversal1(TRAVERSAL_RO, "T6", dh) {
        }

    protected:
        // I made this shorter than in original bench
        int traverse(CompositePart *component) const override;
    };

    // following traversal is actually short traversal, but is here because
    // of it's slightly misleading name
    class LCTraversal7 : public Operation {
    protected:
        LCTraversal7(optype t, const char *n, DataHolder *dh)
                : Operation(t, n, dh) {
        }

    public:
        explicit LCTraversal7(DataHolder *dh)
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

    class LCTraversal8 : public Operation {
    protected:
        LCTraversal8(optype t, const char *n, DataHolder *dh)
                : Operation(t, n, dh) {
        }

    public:
        explicit LCTraversal8(DataHolder *dh)
                : Operation(OPERATION_RO, "T8", dh) {
        }

        int run() const override;

    protected:
        virtual int traverse(Manual *manual) const;
    };

    class LCTraversal9 : public LCTraversal8 {
    public:
        explicit LCTraversal9(DataHolder *dh)
                : LCTraversal8(OPERATION_RO, "T9", dh) {
        }

    protected:
        int traverse(Manual *manual) const override;
    };

}


#endif //STMBENCH_TRAVERSAL_OPS_LC_H
