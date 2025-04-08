#ifndef SB7_LM_SHORT_TRAVERSAL_OPS_H_
#define SB7_LM_SHORT_TRAVERSAL_OPS_H_

#include "../operations.h"
#include "traversal_ops_lm.h"

#include "../../struct/assembly.h"

namespace sb7 {

    class LMShortTraversal1 : public Operation {
    protected:
        LMShortTraversal1(enum optype type, const char *name,
                          DataHolder *dh)
                : Operation(type, name, dh) {
        }

    public:
        LMShortTraversal1(DataHolder *dh)
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

    class LMShortTraversal2 : public LMShortTraversal1 {
    protected:
        LMShortTraversal2(enum optype type, const char *name,
                          DataHolder *dh)
                : LMShortTraversal1(type, name, dh) {
        }

    public:
        LMShortTraversal2(DataHolder *dh) :
                LMShortTraversal1(SHORT_TRAVERSAL_RO, "ST2", dh) {
        }

        virtual int run() const;

    protected:
        virtual int traverse(CompositePart *cpart) const;

        virtual int traverse(AtomicPart *apart) const;

        virtual int traverse(Document *documentation) const;
    };

    class LMShortTraversal6 : public LMShortTraversal1 {
    public:
        LMShortTraversal6(DataHolder *dh) :
                LMShortTraversal1(SHORT_TRAVERSAL, "ST6", dh) {
        }

        virtual int run() const;

    protected:
        virtual int traverse(AtomicPart *apart) const;
    };

    class LMShortTraversal7 : public LMShortTraversal2 {
    public:
        LMShortTraversal7(DataHolder *dh) :
                LMShortTraversal2(SHORT_TRAVERSAL, "ST7", dh) {
        }

        virtual int run() const;

    protected:
        virtual int traverse(Document *documentation) const;
    };

    class LMShortTraversal8 : public LMTraversal7 {
    public:
        LMShortTraversal8(DataHolder *dh) :
                LMTraversal7(SHORT_TRAVERSAL, "ST8", dh) {
        }

        virtual int run() const;

    protected:
        virtual void performOperationOnAssembly(Assembly *assembly) const;
    };

    class LMShortTraversal9 : public LMShortTraversal1 {
    protected:
        LMShortTraversal9(enum optype type, const char *name,
                          DataHolder *dh)
                : LMShortTraversal1(type, name, dh) {
        }

    public:
        LMShortTraversal9(DataHolder *dh) :
                LMShortTraversal1(SHORT_TRAVERSAL_RO, "ST9", dh) {
        }

    protected:
        virtual int traverse(CompositePart *cpart) const;

        virtual int traverse(AtomicPart *apart) const;

        int traverse(AtomicPart *apart,
                     Set<AtomicPart *> &visitedParts) const;

        virtual int performOperationOnAtomicPart(AtomicPart *apart) const;
    };

    class LMShortTraversal10 : public LMShortTraversal9 {
    public:
        LMShortTraversal10(DataHolder *dh) :
                LMShortTraversal9(SHORT_TRAVERSAL, "ST10", dh) {
        }

        virtual int run() const;

    protected:
        virtual int performOperationOnAtomicPart(AtomicPart *apart) const;
    };
}

#endif // SB7_LM_SHORT_TRAVERSAL_OPS_H_
