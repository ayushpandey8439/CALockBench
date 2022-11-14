//
// Created by Ayush Pandey on 15/11/2022.
//

#ifndef STMBENCH_TRAVERSAL_OPS_CA_H
#define STMBENCH_TRAVERSAL_OPS_CA_H


#include "../operations.h"
#include "../../containers.h"
#include "../../struct/assembly.h"

namespace sb7 {

    class CATraversal1 : public Operation {
    protected:
        CATraversal1(optype t, const char *n, DataHolder *dh)
                : Operation(t, n, dh) {
        }

    public:
        explicit CATraversal1(DataHolder *dh) : Operation(TRAVERSAL_RO, "T1", dh) {
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

    class CATraversal2a : public CATraversal1 {
    public:
        explicit CATraversal2a(DataHolder *dh) : CATraversal1(TRAVERSAL, "T2a", dh) {
        }

        int run() const override;

    protected:
        int performOperationOnAtomicPart(AtomicPart *apart,
                                         Set<AtomicPart *> &setOfVisitedPartIds) const override;
    };

    class CATraversal2b : public CATraversal1 {
    public:
        explicit CATraversal2b(DataHolder *dh) : CATraversal1(TRAVERSAL, "T2b", dh) {
        }

        int run() const override;

    protected:
        int performOperationOnAtomicPart(AtomicPart *apart,
                                         Set<AtomicPart *> &setOfVisitedPartIds) const override;
    };

    class CATraversal2c : public CATraversal1 {
    public:
        explicit CATraversal2c(DataHolder *dh) : CATraversal1(TRAVERSAL, "T2c", dh) {
        }

        int run() const override;

    protected:
        int performOperationOnAtomicPart(AtomicPart *apart,
                                         Set<AtomicPart *> &setOfVisitedPartIds) const override;
    };

    class CATraversal3a : public CATraversal1 {
    protected:
        CATraversal3a(optype t, const char *n, DataHolder *dh)
                : CATraversal1(t, n, dh) {
        }

    public:
        explicit CATraversal3a(DataHolder *dh) : CATraversal1(TRAVERSAL, "T3a", dh) {
        }

        int run() const override;

    protected:
        int performOperationOnAtomicPart(AtomicPart *apart,
                                         Set<AtomicPart *> &setOfVisitedPartIds) const override;

        void updateBuildDate(AtomicPart *apart) const;
    };

    class CATraversal3b : public CATraversal3a {
    public:
        explicit CATraversal3b(DataHolder *dh) : CATraversal3a(TRAVERSAL, "T3b", dh) {
        }

    protected:
        int performOperationOnAtomicPart(AtomicPart *apart,
                                         Set<AtomicPart *> &setOfVisitedPartIds) const override;
    };

    class CATraversal3c : public CATraversal3a {
    public:
        explicit CATraversal3c(DataHolder *dh) : CATraversal3a(TRAVERSAL, "T3c", dh) {
        }

    protected:
        int performOperationOnAtomicPart(AtomicPart *apart,
                                         Set<AtomicPart *> &setOfVisitedPartIds) const override;
    };

    class CATraversal4 : public CATraversal1 {
    protected:
        CATraversal4(optype t, const char *n, DataHolder *dh)
                : CATraversal1(t, n, dh) {
        }

    public:
        explicit CATraversal4(DataHolder *dh) : CATraversal1(TRAVERSAL_RO, "T4", dh) {
        }

    protected:
        int traverse(CompositePart *component) const override;

        virtual int traverse(Document *doc) const;

        int traverse(AtomicPart *part,
                     Set<AtomicPart *> &setOfVisitedParts) const override;

        int performOperationOnAtomicPart(AtomicPart *apart,
                                         Set<AtomicPart *> &setOfVisitedPartIds) const override;
    };

    class CATraversal5 : public CATraversal4 {
    public:
        explicit CATraversal5(DataHolder *dh) : CATraversal4(TRAVERSAL, "T5", dh) {
        }

        int run() const override;

    protected:
        int traverse(Document *doc) const override;
    };

    class CATraversal6 : public CATraversal1 {
    public:
        explicit CATraversal6(DataHolder *dh) : CATraversal1(TRAVERSAL_RO, "T6", dh) {
        }

    protected:
        // I made this shorter than in original bench
        int traverse(CompositePart *component) const override;
    };

    // following traversal is actually short traversal, but is here because
    // of it's slightly misleading name
    class CATraversal7 : public Operation {
    protected:
        CATraversal7(optype t, const char *n, DataHolder *dh)
                : Operation(t, n, dh) {
        }

    public:
        explicit CATraversal7(DataHolder *dh)
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

    class CATraversal8 : public Operation {
    protected:
        CATraversal8(optype t, const char *n, DataHolder *dh)
                : Operation(t, n, dh) {
        }

    public:
        explicit CATraversal8(DataHolder *dh)
                : Operation(OPERATION_RO, "T8", dh) {
        }

        int run() const override;

    protected:
        virtual int traverse(Manual *manual) const;
    };

    class CATraversal9 : public CATraversal8 {
    public:
        explicit CATraversal9(DataHolder *dh)
                : CATraversal8(OPERATION_RO, "T9", dh) {
        }

    protected:
        int traverse(Manual *manual) const override;
    };

}



#endif //STMBENCH_TRAVERSAL_OPS_CA_H
