#ifndef SB7_Dom_SHORT_TRAVERSAL_OPS_H_
#define SB7_Dom_SHORT_TRAVERSAL_OPS_H_

#include "../operations.h"
#include "traversal_ops_dom.h"

#include "../../struct/assembly.h"

namespace sb7 {

    class DomShortTraversal1 : public Operation {
    protected:
        DomShortTraversal1(enum optype type, const char *name,
                           DataHolder *dh)
                : Operation(type, name, dh) {
        }

    public:
        DomShortTraversal1(DataHolder *dh)
                : Operation(SHORT_TRAVERSAL_RO, "ST1", dh) {
        }

        virtual int run() const;

    protected:
        int traverse(Assembly *assm) const;

        int traverse(ComplexAssembly *cassm) const;

        int traverse(BaseAssembly *bassm) const;

        virtual int traverse(CompositePart *cpart) const;

        virtual int traverse(AtomicPart *apart) const;
    };

    class DomShortTraversal2 : public DomShortTraversal1 {
    protected:
        DomShortTraversal2(enum optype type, const char *name,
                           DataHolder *dh)
                : DomShortTraversal1(type, name, dh) {
        }

    public:
        DomShortTraversal2(DataHolder *dh) :
                DomShortTraversal1(SHORT_TRAVERSAL_RO, "ST2", dh) {
        }

    protected:
        virtual int traverse(CompositePart *cpart) const;

        virtual int traverse(AtomicPart *apart) const;

        virtual int traverse(Document *documentation) const;
    };

    class DomShortTraversal6 : public DomShortTraversal1 {
    public:
        DomShortTraversal6(DataHolder *dh) :
                DomShortTraversal1(SHORT_TRAVERSAL, "ST6", dh) {
        }

        virtual int run() const;

    protected:
        virtual int traverse(AtomicPart *apart) const;
    };

    class DomShortTraversal7 : public DomShortTraversal2 {
    public:
        DomShortTraversal7(DataHolder *dh) :
                DomShortTraversal2(SHORT_TRAVERSAL, "ST7", dh) {
        }

        virtual int run() const;

    protected:
        virtual int traverse(Document *documentation) const;
    };

    class DomShortTraversal8 : public DomTraversal7 {
    public:
        DomShortTraversal8(DataHolder *dh) :
                DomTraversal7(SHORT_TRAVERSAL, "ST8", dh) {
        }

        virtual int run() const;

    protected:
        virtual void performOperationOnAssembly(Assembly *assembly) const;
    };

    class DomShortTraversal9 : public DomShortTraversal1 {
    protected:
        DomShortTraversal9(enum optype type, const char *name,
                           DataHolder *dh)
                : DomShortTraversal1(type, name, dh) {
        }

    public:
        DomShortTraversal9(DataHolder *dh) :
                DomShortTraversal1(SHORT_TRAVERSAL_RO, "ST9", dh) {
        }

    protected:
        virtual int traverse(CompositePart *cpart) const;

        virtual int traverse(AtomicPart *apart) const;

        int traverse(AtomicPart *apart,
                     Set<AtomicPart *> &visitedParts) const;

        virtual int performOperationOnAtomicPart(AtomicPart *apart) const;
    };

    class DomShortTraversal10 : public DomShortTraversal9 {
    public:
        DomShortTraversal10(DataHolder *dh) :
                DomShortTraversal9(SHORT_TRAVERSAL, "ST10", dh) {
        }

        virtual int run() const;

    protected:
        virtual int performOperationOnAtomicPart(AtomicPart *apart) const;
    };
}

#endif // SB7_Dom_SHORT_TRAVERSAL_OPS_H_
