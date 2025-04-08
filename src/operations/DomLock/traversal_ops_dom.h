#ifndef SB7_Dom_TRAVERSAL_OPS_
#define SB7_Dom_TRAVERSAL_OPS_

#include "../operations.h"
#include "../../containers.h"
#include "../../struct/assembly.h"

namespace sb7 {

    class DomTraversal1 : public Operation {
    protected:
        DomTraversal1(optype t, const char *n, DataHolder *dh)
                : Operation(t, n, dh) {
        }

    public:
        DomTraversal1(DataHolder *dh) : Operation(TRAVERSAL_RO, "T1", dh) {
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

    class DomTraversal2a : public DomTraversal1 {
    public:
        DomTraversal2a(DataHolder *dh) : DomTraversal1(TRAVERSAL, "T2a", dh) {
        }

        virtual int run() const;

    protected:
        virtual int performOperationOnAtomicPart(AtomicPart *apart,
                                                 Set<AtomicPart *> &setOfVisitedPartIds) const;
    };

    class DomTraversal2b : public DomTraversal1 {
    public:
        DomTraversal2b(DataHolder *dh) : DomTraversal1(TRAVERSAL, "T2b", dh) {
        }

        virtual int run() const;

    protected:
        virtual int performOperationOnAtomicPart(AtomicPart *apart,
                                                 Set<AtomicPart *> &setOfVisitedPartIds) const;
    };

    class DomTraversal2c : public DomTraversal1 {
    public:
        DomTraversal2c(DataHolder *dh) : DomTraversal1(TRAVERSAL, "T2c", dh) {
        }

        virtual int run() const;

    protected:
        virtual int performOperationOnAtomicPart(AtomicPart *apart,
                                                 Set<AtomicPart *> &setOfVisitedPartIds) const;
    };

    class DomTraversal3a : public DomTraversal1 {
    protected:
        DomTraversal3a(optype t, const char *n, DataHolder *dh)
                : DomTraversal1(t, n, dh) {
        }

    public:
        DomTraversal3a(DataHolder *dh) : DomTraversal1(TRAVERSAL, "T3a", dh) {
        }

        virtual int run() const;

    protected:
        virtual int performOperationOnAtomicPart(AtomicPart *apart,
                                                 Set<AtomicPart *> &setOfVisitedPartIds) const;

        void updateBuildDate(AtomicPart *apart) const;
    };

    class DomTraversal3b : public DomTraversal3a {
    public:
        DomTraversal3b(DataHolder *dh) : DomTraversal3a(TRAVERSAL, "T3b", dh) {
        }

    protected:
        virtual int performOperationOnAtomicPart(AtomicPart *apart,
                                                 Set<AtomicPart *> &setOfVisitedPartIds) const;
    };

    class DomTraversal3c : public DomTraversal3a {
    public:
        DomTraversal3c(DataHolder *dh) : DomTraversal3a(TRAVERSAL, "T3c", dh) {
        }

    protected:
        virtual int performOperationOnAtomicPart(AtomicPart *apart,
                                                 Set<AtomicPart *> &setOfVisitedPartIds) const;
    };

    class DomTraversal4 : public DomTraversal1 {
    protected:
        DomTraversal4(optype t, const char *n, DataHolder *dh)
                : DomTraversal1(t, n, dh) {
        }

    public:
        DomTraversal4(DataHolder *dh) : DomTraversal1(TRAVERSAL_RO, "T4", dh) {
        }

    protected:
        virtual int traverse(CompositePart *component) const;

        virtual int traverse(Document *doc) const;

        virtual int traverse(AtomicPart *part,
                             Set<AtomicPart *> &setOfVisitedParts) const;

        virtual int performOperationOnAtomicPart(AtomicPart *apart,
                                                 Set<AtomicPart *> &setOfVisitedPartIds) const;
    };

    class DomTraversal5 : public DomTraversal4 {
    public:
        DomTraversal5(DataHolder *dh) : DomTraversal4(TRAVERSAL, "T5", dh) {
        }

        virtual int run() const;

    protected:
        virtual int traverse(Document *doc) const;
    };

    class DomTraversal6 : public DomTraversal1 {
    public:
        DomTraversal6(DataHolder *dh) : DomTraversal1(TRAVERSAL_RO, "T6", dh) {
        }

    protected:
        // I made this shorter than in original bench
        virtual int traverse(CompositePart *component) const;
    };

    // following traversal is actually short traversal, but is here because
    // of it's slightly misleading name
    class DomTraversal7 : public Operation {
    protected:
        DomTraversal7(optype t, const char *n, DataHolder *dh)
                : Operation(t, n, dh) {
        }

    public:
        DomTraversal7(DataHolder *dh)
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

    class DomTraversal8 : public Operation {
    protected:
        DomTraversal8(optype t, const char *n, DataHolder *dh)
                : Operation(t, n, dh) {
        }

    public:
        DomTraversal8(DataHolder *dh)
                : Operation(OPERATION_RO, "T8", dh) {
        }

        virtual int run() const;

    protected:
        virtual int traverse(Manual *manual) const;
    };

    class DomTraversal9 : public DomTraversal8 {
    public:
        DomTraversal9(DataHolder *dh)
                : DomTraversal8(OPERATION_RO, "T9", dh) {
        }

    protected:
        virtual int traverse(Manual *manual) const;
    };

}

#endif // SB7_Dom_TRAVERSAL_OPS_
