#ifndef SB7_Mid_SHORT_TRAVERSAL_OPS_H_
#define SB7_Mid_SHORT_TRAVERSAL_OPS_H_

#include "../operations.h"
#include "traversal_ops_num.h"

#include "../../struct/assembly.h"

namespace sb7 {

    class MidShortTraversal1 : public Operation {
    protected:
        MidShortTraversal1(enum optype type, const char *name,
                          DataHolder *dh)
                : Operation(type, name, dh) {
        }

    public:
        MidShortTraversal1(DataHolder *dh)
                : Operation(SHORT_TRAVERSAL_RO, "ST1", dh) {
        }

        virtual int run(int tid) const;

    protected:
        int traverse(Assembly *assm) const;

        int traverse(ComplexAssembly *cassm) const;

        int traverse(BaseAssembly *bassm) const;

        virtual int traverse(CompositePart *cpart) const;

        virtual int traverse(AtomicPart *apart) const;
    };

    class MidShortTraversal2 : public MidShortTraversal1 {
    protected:
        MidShortTraversal2(enum optype type, const char *name,
                          DataHolder *dh)
                : MidShortTraversal1(type, name, dh) {
        }

    public:
        MidShortTraversal2(DataHolder *dh) :
                MidShortTraversal1(SHORT_TRAVERSAL_RO, "ST2", dh) {
        }

        virtual int run(int tid) const;

    protected:
        virtual int traverse(CompositePart *cpart) const;

        virtual int traverse(AtomicPart *apart) const;

        virtual int traverse(Document *documentation) const;
    };

    class MidShortTraversal6 : public MidShortTraversal1 {
    public:
        MidShortTraversal6(DataHolder *dh) :
                MidShortTraversal1(SHORT_TRAVERSAL, "ST6", dh) {
        }

        virtual int run(int tid) const;

    protected:
        virtual int traverse(AtomicPart *apart) const;
    };

    class MidShortTraversal7 : public MidShortTraversal2 {
    public:
        MidShortTraversal7(DataHolder *dh) :
                MidShortTraversal2(SHORT_TRAVERSAL, "ST7", dh) {
        }

        virtual int run(int tid) const;

    protected:
        virtual int traverse(Document *documentation) const;
    };

    class MidShortTraversal8 : public MidTraversal7 {
    public:
        MidShortTraversal8(DataHolder *dh) :
                MidTraversal7(SHORT_TRAVERSAL, "ST8", dh) {
        }

        virtual int run(int tid) const;

    protected:
        virtual void performOperationOnAssembly(Assembly *assembly) const;
    };

    class MidShortTraversal9 : public MidShortTraversal1 {
    protected:
        MidShortTraversal9(enum optype type, const char *name,
                          DataHolder *dh)
                : MidShortTraversal1(type, name, dh) {
        }

    public:
        MidShortTraversal9(DataHolder *dh) :
                MidShortTraversal1(SHORT_TRAVERSAL_RO, "ST9", dh) {
        }

    protected:
        virtual int traverse(CompositePart *cpart) const;

        virtual int traverse(AtomicPart *apart) const;

        int traverse(AtomicPart *apart,
                     Set<AtomicPart *> &visitedParts) const;

        virtual int performOperationOnAtomicPart(AtomicPart *apart) const;
    };

    class MidShortTraversal10 : public MidShortTraversal9 {
    public:
        MidShortTraversal10(DataHolder *dh) :
                MidShortTraversal9(SHORT_TRAVERSAL, "ST10", dh) {
        }

        virtual int run(int tid) const;

    protected:
        virtual int performOperationOnAtomicPart(AtomicPart *apart) const;
    };
}

#endif // SB7_Mid_SHORT_TRAVERSAL_OPS_H_
