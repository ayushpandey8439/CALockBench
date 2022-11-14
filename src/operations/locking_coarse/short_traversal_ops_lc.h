//
// Created by Ayush Pandey on 15/11/2022.
//

#ifndef STMBENCH_SHORT_TRAVERSAL_OPS_LC_H
#define STMBENCH_SHORT_TRAVERSAL_OPS_LC_H


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
        explicit LCShortTraversal1(DataHolder *dh)
                : Operation(SHORT_TRAVERSAL_RO, "ST1", dh) {
        }

        int run() const override;

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
        explicit LCShortTraversal2(DataHolder *dh) :
                LCShortTraversal1(SHORT_TRAVERSAL_RO, "ST2", dh) {
        }

    protected:
        int traverse(CompositePart *cpart) const override;

        int traverse(AtomicPart *apart) const override;

        virtual int traverse(Document *documentation) const;
    };

    class LCShortTraversal6 : public LCShortTraversal1 {
    public:
        explicit LCShortTraversal6(DataHolder *dh) :
                LCShortTraversal1(SHORT_TRAVERSAL, "ST6", dh) {
        }

        int run() const override;

    protected:
        int traverse(AtomicPart *apart) const override;
    };

    class LCShortTraversal7 : public LCShortTraversal2 {
    public:
        explicit LCShortTraversal7(DataHolder *dh) :
                LCShortTraversal2(SHORT_TRAVERSAL, "ST7", dh) {
        }

        int run() const override;

    protected:
        int traverse(Document *documentation) const override;
    };

    class LCShortTraversal8 : public LCTraversal7 {
    public:
        explicit LCShortTraversal8(DataHolder *dh) :
                LCTraversal7(SHORT_TRAVERSAL, "ST8", dh) {
        }

        int run() const override;

    protected:
        void performOperationOnAssembly(Assembly *assembly) const override;
    };

    class LCShortTraversal9 : public LCShortTraversal1 {
    protected:
        LCShortTraversal9(enum optype type, const char *name,
                          DataHolder *dh)
                : LCShortTraversal1(type, name, dh) {
        }

    public:
        explicit LCShortTraversal9(DataHolder *dh) :
                LCShortTraversal1(SHORT_TRAVERSAL_RO, "ST9", dh) {
        }

    protected:
        int traverse(CompositePart *cpart) const override;

        int traverse(AtomicPart *apart) const override;

        int traverse(AtomicPart *apart,
                     Set<AtomicPart *> &visitedParts) const;

        virtual int performOperationOnAtomicPart(AtomicPart *apart) const;
    };

    class LCShortTraversal10 : public LCShortTraversal9 {
    public:
        explicit LCShortTraversal10(DataHolder *dh) :
                LCShortTraversal9(SHORT_TRAVERSAL, "ST10", dh) {
        }

        int run() const override;

    protected:
        int performOperationOnAtomicPart(AtomicPart *apart) const override;
    };
}


#endif //STMBENCH_SHORT_TRAVERSAL_OPS_LC_H
