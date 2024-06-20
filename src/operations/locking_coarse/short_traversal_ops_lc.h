#ifndef SB7_LC_SHORT_TRAVERSAL_OPS_H_
#define SB7_LC_SHORT_TRAVERSAL_OPS_H_

#include "../operations.h"
#include "traversal_ops_lc.h"

#include "../../struct/assembly.h"

namespace sb7 {

    class LCShortTraversal1 : public Operation {
    protected:
        LCShortTraversal1(enum optype type, const char *name,
                          DataHolder *dh)
                : Operation(type, name, dh) {
        }

    public:
        LCShortTraversal1(DataHolder *dh)
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

    class LCShortTraversal2 : public LCShortTraversal1 {
    protected:
        LCShortTraversal2(enum optype type, const char *name,
                          DataHolder *dh)
                : LCShortTraversal1(type, name, dh) {
        }

    public:
        LCShortTraversal2(DataHolder *dh) :
                LCShortTraversal1(SHORT_TRAVERSAL_RO, "ST2", dh) {
        }

    protected:
        virtual int traverse(CompositePart *cpart) const;

        virtual int traverse(AtomicPart *apart) const;

        virtual int traverse(Document *documentation) const;
    };

    class LCShortTraversal6 : public LCShortTraversal1 {
    public:
        LCShortTraversal6(DataHolder *dh) :
                LCShortTraversal1(SHORT_TRAVERSAL, "ST6", dh) {
        }

        virtual int run() const;

    protected:
        virtual int traverse(AtomicPart *apart) const;
    };

    class LCShortTraversal7 : public LCShortTraversal2 {
    public:
        LCShortTraversal7(DataHolder *dh) :
                LCShortTraversal2(SHORT_TRAVERSAL, "ST7", dh) {
        }

        virtual int run() const;

    protected:
        virtual int traverse(Document *documentation) const;
    };

    class LCShortTraversal8 : public LCTraversal7 {
    public:
        LCShortTraversal8(DataHolder *dh) :
                LCTraversal7(SHORT_TRAVERSAL, "ST8", dh) {
        }

        virtual int run() const;

    protected:
        virtual void performOperationOnAssembly(Assembly *assembly) const;
    };

    class LCShortTraversal9 : public LCShortTraversal1 {
    protected:
        LCShortTraversal9(enum optype type, const char *name,
                          DataHolder *dh)
                : LCShortTraversal1(type, name, dh) {
        }

    public:
        LCShortTraversal9(DataHolder *dh) :
                LCShortTraversal1(SHORT_TRAVERSAL_RO, "ST9", dh) {
        }

    protected:
        virtual int traverse(CompositePart *cpart) const;

        virtual int traverse(AtomicPart *apart) const;

        int traverse(AtomicPart *apart,
                     Set<AtomicPart *> &visitedParts) const;

        virtual int performOperationOnAtomicPart(AtomicPart *apart) const;
    };

    class LCShortTraversal10 : public LCShortTraversal9 {
    public:
        LCShortTraversal10(DataHolder *dh) :
                LCShortTraversal9(SHORT_TRAVERSAL, "ST10", dh) {
        }

        virtual int run() const;

    protected:
        virtual int performOperationOnAtomicPart(AtomicPart *apart) const;
    };
}

#endif // SB7_LC_SHORT_TRAVERSAL_OPS_H_
