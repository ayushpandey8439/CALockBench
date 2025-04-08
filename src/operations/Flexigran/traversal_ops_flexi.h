#ifndef SB7_Flexi_TRAVERSAL_OPS_
#define SB7_Flexi_TRAVERSAL_OPS_

#include "../operations.h"
#include "../../containers.h"
#include "../../struct/assembly.h"

namespace sb7 {

    class FlexiTraversal1 : public Operation {
    protected:
        FlexiTraversal1(optype t, const char *n, DataHolder *dh)
                : Operation(t, n, dh) {
        }

    public:
        FlexiTraversal1(DataHolder *dh) : Operation(TRAVERSAL_RO, "T1", dh) {
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

    class FlexiTraversal2a : public FlexiTraversal1 {
    public:
        FlexiTraversal2a(DataHolder *dh) : FlexiTraversal1(TRAVERSAL, "T2a", dh) {
        }

        virtual int run() const;

    protected:
        virtual int performOperationOnAtomicPart(AtomicPart *apart,
                                                 Set<AtomicPart *> &setOfVisitedPartIds) const;
    };

    class FlexiTraversal2b : public FlexiTraversal1 {
    public:
        FlexiTraversal2b(DataHolder *dh) : FlexiTraversal1(TRAVERSAL, "T2b", dh) {
        }

        virtual int run() const;

    protected:
        virtual int performOperationOnAtomicPart(AtomicPart *apart,
                                                 Set<AtomicPart *> &setOfVisitedPartIds) const;
    };

    class FlexiTraversal2c : public FlexiTraversal1 {
    public:
        FlexiTraversal2c(DataHolder *dh) : FlexiTraversal1(TRAVERSAL, "T2c", dh) {
        }

        virtual int run() const;

    protected:
        virtual int performOperationOnAtomicPart(AtomicPart *apart,
                                                 Set<AtomicPart *> &setOfVisitedPartIds) const;
    };

    class FlexiTraversal3a : public FlexiTraversal1 {
    protected:
        FlexiTraversal3a(optype t, const char *n, DataHolder *dh)
                : FlexiTraversal1(t, n, dh) {
        }

    public:
        FlexiTraversal3a(DataHolder *dh) : FlexiTraversal1(TRAVERSAL, "T3a", dh) {
        }

        virtual int run() const;

    protected:
        virtual int performOperationOnAtomicPart(AtomicPart *apart,
                                                 Set<AtomicPart *> &setOfVisitedPartIds) const;

        void updateBuildDate(AtomicPart *apart) const;
    };

    class FlexiTraversal3b : public FlexiTraversal3a {
    public:
        FlexiTraversal3b(DataHolder *dh) : FlexiTraversal3a(TRAVERSAL, "T3b", dh) {
        }

    protected:
        virtual int performOperationOnAtomicPart(AtomicPart *apart,
                                                 Set<AtomicPart *> &setOfVisitedPartIds) const;
    };

    class FlexiTraversal3c : public FlexiTraversal3a {
    public:
        FlexiTraversal3c(DataHolder *dh) : FlexiTraversal3a(TRAVERSAL, "T3c", dh) {
        }

    protected:
        virtual int performOperationOnAtomicPart(AtomicPart *apart,
                                                 Set<AtomicPart *> &setOfVisitedPartIds) const;
    };

    class FlexiTraversal4 : public FlexiTraversal1 {
    protected:
        FlexiTraversal4(optype t, const char *n, DataHolder *dh)
                : FlexiTraversal1(t, n, dh) {
        }

    public:
        FlexiTraversal4(DataHolder *dh) : FlexiTraversal1(TRAVERSAL_RO, "T4", dh) {
        }

    protected:
        virtual int traverse(CompositePart *component) const;

        virtual int traverse(Document *doc) const;

        virtual int traverse(AtomicPart *part,
                             Set<AtomicPart *> &setOfVisitedParts) const;

        virtual int performOperationOnAtomicPart(AtomicPart *apart,
                                                 Set<AtomicPart *> &setOfVisitedPartIds) const;
    };

    class FlexiTraversal5 : public FlexiTraversal4 {
    public:
        FlexiTraversal5(DataHolder *dh) : FlexiTraversal4(TRAVERSAL, "T5", dh) {
        }

        virtual int run() const;

    protected:
        virtual int traverse(Document *doc) const;
    };

    class FlexiTraversal6 : public FlexiTraversal1 {
    public:
        FlexiTraversal6(DataHolder *dh) : FlexiTraversal1(TRAVERSAL_RO, "T6", dh) {
        }

    protected:
        // I made this shorter than in original bench
        virtual int traverse(CompositePart *component) const;
    };

    // following traversal is actually short traversal, but is here because
    // of it's slightly misleading name
    class FlexiTraversal7 : public Operation {
    protected:
        FlexiTraversal7(optype t, const char *n, DataHolder *dh)
                : Operation(t, n, dh) {
        }

    public:
        FlexiTraversal7(DataHolder *dh)
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

    class FlexiTraversal8 : public Operation {
    protected:
        FlexiTraversal8(optype t, const char *n, DataHolder *dh)
                : Operation(t, n, dh) {
        }

    public:
        FlexiTraversal8(DataHolder *dh)
                : Operation(OPERATION_RO, "T8", dh) {
        }

        virtual int run() const;

    protected:
        virtual int traverse(Manual *manual) const;
    };

    class FlexiTraversal9 : public FlexiTraversal8 {
    public:
        FlexiTraversal9(DataHolder *dh)
                : FlexiTraversal8(OPERATION_RO, "T9", dh) {
        }

    protected:
        virtual int traverse(Manual *manual) const;
    };

}

#endif // SB7_Flexi_TRAVERSAL_OPS_
