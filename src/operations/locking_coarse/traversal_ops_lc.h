#ifndef SB7_LC_TRAVERSAL_OPS_
#define SB7_LC_TRAVERSAL_OPS_

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
        LCTraversal1(DataHolder *dh) : Operation(TRAVERSAL_RO, "T1", dh) {
        }

        virtual int run() const;

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
        LCTraversal2a(DataHolder *dh) : LCTraversal1(TRAVERSAL, "T2a", dh) {
        }

        virtual int run() const;

    protected:
        virtual int performOperationOnAtomicPart(AtomicPart *apart,
                                                 Set<AtomicPart *> &setOfVisitedPartIds) const;
    };

    class LCTraversal2b : public LCTraversal1 {
    public:
        LCTraversal2b(DataHolder *dh) : LCTraversal1(TRAVERSAL, "T2b", dh) {
        }

        virtual int run() const;

    protected:
        virtual int performOperationOnAtomicPart(AtomicPart *apart,
                                                 Set<AtomicPart *> &setOfVisitedPartIds) const;
    };

    class LCTraversal2c : public LCTraversal1 {
    public:
        LCTraversal2c(DataHolder *dh) : LCTraversal1(TRAVERSAL, "T2c", dh) {
        }

        virtual int run() const;

    protected:
        virtual int performOperationOnAtomicPart(AtomicPart *apart,
                                                 Set<AtomicPart *> &setOfVisitedPartIds) const;
    };

    class LCTraversal3a : public LCTraversal1 {
    protected:
        LCTraversal3a(optype t, const char *n, DataHolder *dh)
                : LCTraversal1(t, n, dh) {
        }

    public:
        LCTraversal3a(DataHolder *dh) : LCTraversal1(TRAVERSAL, "T3a", dh) {
        }

        virtual int run() const;

    protected:
        virtual int performOperationOnAtomicPart(AtomicPart *apart,
                                                 Set<AtomicPart *> &setOfVisitedPartIds) const;

        void updateBuildDate(AtomicPart *apart) const;
    };

    class LCTraversal3b : public LCTraversal3a {
    public:
        LCTraversal3b(DataHolder *dh) : LCTraversal3a(TRAVERSAL, "T3b", dh) {
        }

    protected:
        virtual int performOperationOnAtomicPart(AtomicPart *apart,
                                                 Set<AtomicPart *> &setOfVisitedPartIds) const;
    };

    class LCTraversal3c : public LCTraversal3a {
    public:
        LCTraversal3c(DataHolder *dh) : LCTraversal3a(TRAVERSAL, "T3c", dh) {
        }

    protected:
        virtual int performOperationOnAtomicPart(AtomicPart *apart,
                                                 Set<AtomicPart *> &setOfVisitedPartIds) const;
    };

    class LCTraversal4 : public LCTraversal1 {
    protected:
        LCTraversal4(optype t, const char *n, DataHolder *dh)
                : LCTraversal1(t, n, dh) {
        }

    public:
        LCTraversal4(DataHolder *dh) : LCTraversal1(TRAVERSAL_RO, "T4", dh) {
        }

    protected:
        virtual int traverse(CompositePart *component) const;

        virtual int traverse(Document *doc) const;

        virtual int traverse(AtomicPart *part,
                             Set<AtomicPart *> &setOfVisitedParts) const;

        virtual int performOperationOnAtomicPart(AtomicPart *apart,
                                                 Set<AtomicPart *> &setOfVisitedPartIds) const;
    };

    class LCTraversal5 : public LCTraversal4 {
    public:
        LCTraversal5(DataHolder *dh) : LCTraversal4(TRAVERSAL, "T5", dh) {
        }

        virtual int run() const;

    protected:
        virtual int traverse(Document *doc) const;
    };

    class LCTraversal6 : public LCTraversal1 {
    public:
        LCTraversal6(DataHolder *dh) : LCTraversal1(TRAVERSAL_RO, "T6", dh) {
        }

    protected:
        // I made this shorter than in original bench
        virtual int traverse(CompositePart *component) const;
    };

    // following traversal is actually short traversal, but is here because
    // of it's slightly misleading name
    class LCTraversal7 : public Operation {
    protected:
        LCTraversal7(optype t, const char *n, DataHolder *dh)
                : Operation(t, n, dh) {
        }

    public:
        LCTraversal7(DataHolder *dh)
                : Operation(SHORT_TRAVERSAL_RO, "T7", dh) {
        }

        virtual int run() const;

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
        LCTraversal8(DataHolder *dh)
                : Operation(OPERATION_RO, "T8", dh) {
        }

        virtual int run() const;

    protected:
        virtual int traverse(Manual *manual) const;
    };

    class LCTraversal9 : public LCTraversal8 {
    public:
        LCTraversal9(DataHolder *dh)
                : LCTraversal8(OPERATION_RO, "T9", dh) {
        }

    protected:
        virtual int traverse(Manual *manual) const;
    };

}

#endif // SB7_LC_TRAVERSAL_OPS_
