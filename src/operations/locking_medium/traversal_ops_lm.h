#ifndef SB7_LM_TRAVERSAL_OPS_
#define SB7_LM_TRAVERSAL_OPS_

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
        LMTraversal1(DataHolder *dh) : Operation(TRAVERSAL_RO, "T1", dh) {
        }

        int run(int tid) const override;

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
        LMTraversal2a(DataHolder *dh) : LMTraversal1(TRAVERSAL, "T2a", dh) {
        }

        int run(int tid) const override;

    protected:
        virtual int performOperationOnAtomicPart(AtomicPart *apart,
                                                 Set<AtomicPart *> &setOfVisitedPartIds) const;
    };

    class LMTraversal2b : public LMTraversal1 {
    public:
        LMTraversal2b(DataHolder *dh) : LMTraversal1(TRAVERSAL, "T2b", dh) {
        }

        int run(int tid) const override;

    protected:
        virtual int performOperationOnAtomicPart(AtomicPart *apart,
                                                 Set<AtomicPart *> &setOfVisitedPartIds) const;
    };

    class LMTraversal2c : public LMTraversal1 {
    public:
        LMTraversal2c(DataHolder *dh) : LMTraversal1(TRAVERSAL, "T2c", dh) {
        }

        int run(int tid) const override;

    protected:
        virtual int performOperationOnAtomicPart(AtomicPart *apart,
                                                 Set<AtomicPart *> &setOfVisitedPartIds) const;
    };

    class LMTraversal3a : public LMTraversal1 {
    protected:
        LMTraversal3a(optype t, const char *n, DataHolder *dh)
                : LMTraversal1(t, n, dh) {
        }

    public:
        LMTraversal3a(DataHolder *dh) : LMTraversal1(TRAVERSAL, "T3a", dh) {
        }

        int run(int tid) const override;

    protected:
        virtual int performOperationOnAtomicPart(AtomicPart *apart,
                                                 Set<AtomicPart *> &setOfVisitedPartIds) const;

        void updateBuildDate(AtomicPart *apart) const;
    };

    class LMTraversal3b : public LMTraversal3a {
    public:
        LMTraversal3b(DataHolder *dh) : LMTraversal3a(TRAVERSAL, "T3b", dh) {
        }

    protected:
        virtual int performOperationOnAtomicPart(AtomicPart *apart,
                                                 Set<AtomicPart *> &setOfVisitedPartIds) const;
    };

    class LMTraversal3c : public LMTraversal3a {
    public:
        LMTraversal3c(DataHolder *dh) : LMTraversal3a(TRAVERSAL, "T3c", dh) {
        }

    protected:
        virtual int performOperationOnAtomicPart(AtomicPart *apart,
                                                 Set<AtomicPart *> &setOfVisitedPartIds) const;
    };

    class LMTraversal4 : public LMTraversal1 {
    protected:
        LMTraversal4(optype t, const char *n, DataHolder *dh)
                : LMTraversal1(t, n, dh) {
        }

    public:
        LMTraversal4(DataHolder *dh) : LMTraversal1(TRAVERSAL_RO, "T4", dh) {
        }

        int run(int tid) const override;

    protected:
        virtual int traverse(CompositePart *component) const;

        virtual int traverse(Document *doc) const;

        virtual int traverse(AtomicPart *part,
                             Set<AtomicPart *> &setOfVisitedParts) const;

        virtual int performOperationOnAtomicPart(AtomicPart *apart,
                                                 Set<AtomicPart *> &setOfVisitedPartIds) const;
    };

    class LMTraversal5 : public LMTraversal4 {
    public:
        LMTraversal5(DataHolder *dh) : LMTraversal4(TRAVERSAL, "T5", dh) {
        }

        int run(int tid) const override;

    protected:
        virtual int traverse(Document *doc) const;
    };

    class LMTraversal6 : public LMTraversal1 {
    public:
        LMTraversal6(DataHolder *dh) : LMTraversal1(TRAVERSAL_RO, "T6", dh) {
        }

    protected:
        // I made this shorter than in original bench
        virtual int traverse(CompositePart *component) const;
    };

    // following traversal is actually short traversal, but is here because
    // of it's slightly misleading name
    class LMTraversal7 : public Operation {
    protected:
        LMTraversal7(optype t, const char *n, DataHolder *dh)
                : Operation(t, n, dh) {
        }

    public:
        LMTraversal7(DataHolder *dh)
                : Operation(SHORT_TRAVERSAL_RO, "T7", dh) {
        }

        int run(int tid) const override;

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
        LMTraversal8(DataHolder *dh)
                : Operation(OPERATION_RO, "T8", dh) {
        }

        int run(int tid) const override;

    protected:
        virtual int traverse(Manual *manual) const;
    };

    class LMTraversal9 : public LMTraversal8 {
    public:
        LMTraversal9(DataHolder *dh)
                : LMTraversal8(OPERATION_RO, "T9", dh) {
        }

    protected:
        virtual int traverse(Manual *manual) const;
    };

}

#endif // SB7_LM_TRAVERSAL_OPS_
