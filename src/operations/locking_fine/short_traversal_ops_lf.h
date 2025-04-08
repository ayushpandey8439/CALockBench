#ifndef SB7_LF_SHORT_TRAVERSAL_OPS_H_
#define SB7_LF_SHORT_TRAVERSAL_OPS_H_

#include "../operations.h"
#include "traversal_ops_lf.h"

#include "../../struct/assembly.h"

namespace sb7 {

    class LFShortTraversal1 : public Operation {
    protected:
        LFShortTraversal1(enum optype type, const char *name,
                          DataHolder *dh)
                : Operation(type, name, dh) {
        }

    public:
        LFShortTraversal1(DataHolder *dh)
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

    class LFShortTraversal2 : public LFShortTraversal1 {
    protected:
        LFShortTraversal2(enum optype type, const char *name,
                          DataHolder *dh)
                : LFShortTraversal1(type, name, dh) {
        }

    public:
        LFShortTraversal2(DataHolder *dh) :
                LFShortTraversal1(SHORT_TRAVERSAL_RO, "ST2", dh) {
        }

    protected:
        virtual int traverse(CompositePart *cpart) const;

        virtual int traverse(AtomicPart *apart) const;

        virtual int traverse(Document *documentation) const;
    };

    class LFShortTraversal6 : public LFShortTraversal1 {
    public:
        LFShortTraversal6(DataHolder *dh) :
                LFShortTraversal1(SHORT_TRAVERSAL, "ST6", dh) {
        }

    protected:
        virtual int traverse(AtomicPart *apart) const;
    };

    class LFShortTraversal7 : public LFShortTraversal2 {
    public:
        LFShortTraversal7(DataHolder *dh) :
                LFShortTraversal2(SHORT_TRAVERSAL, "ST7", dh) {
        }

    protected:
        virtual int traverse(Document *documentation) const;
    };

    class LFShortTraversal8 : public LFTraversal7 {
    public:
        LFShortTraversal8(DataHolder *dh) :
                LFTraversal7(SHORT_TRAVERSAL, "ST8", dh) {
        }

    protected:
        virtual void performOperationOnAssembly(Assembly *assembly) const;
    };

    class LFShortTraversal9 : public LFShortTraversal1 {
    protected:
        LFShortTraversal9(enum optype type, const char *name,
                          DataHolder *dh)
                : LFShortTraversal1(type, name, dh) {
        }

    public:
        LFShortTraversal9(DataHolder *dh) :
                LFShortTraversal1(SHORT_TRAVERSAL_RO, "ST9", dh) {
        }

    protected:
        virtual int traverse(CompositePart *cpart) const;

        virtual int traverse(AtomicPart *apart) const;

        int traverse(AtomicPart *apart,
                     Set<AtomicPart *> &visitedParts) const;

        virtual int performOperationOnAtomicPart(AtomicPart *apart) const;
    };

    class LFShortTraversal10 : public LFShortTraversal9 {
    public:
        LFShortTraversal10(DataHolder *dh) :
                LFShortTraversal9(SHORT_TRAVERSAL, "ST10", dh) {
        }

        virtual int performOperationOnAtomicPart(AtomicPart *apart) const;
    };
}

#endif // SB7_LF_SHORT_TRAVERSAL_OPS_H_
