//
// Created by Ayush Pandey on 15/11/2022.
//

#ifndef STMBENCH_SHORT_TRAVERSAL_OPS_LM_H
#define STMBENCH_SHORT_TRAVERSAL_OPS_LM_H


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
        explicit LMShortTraversal1(DataHolder *dh)
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

    class LMShortTraversal2 : public LMShortTraversal1 {
    protected:
        LMShortTraversal2(enum optype type, const char *name,
                          DataHolder *dh)
                : LMShortTraversal1(type, name, dh) {
        }

    public:
        explicit LMShortTraversal2(DataHolder *dh) :
                LMShortTraversal1(SHORT_TRAVERSAL_RO, "ST2", dh) {
        }

        int run() const override;

    protected:
        int traverse(CompositePart *cpart) const override;

        int traverse(AtomicPart *apart) const override;

        virtual int traverse(Document *documentation) const;
    };

    class LMShortTraversal6 : public LMShortTraversal1 {
    public:
        explicit LMShortTraversal6(DataHolder *dh) :
                LMShortTraversal1(SHORT_TRAVERSAL, "ST6", dh) {
        }

        int run() const override;

    protected:
        int traverse(AtomicPart *apart) const override;
    };

    class LMShortTraversal7 : public LMShortTraversal2 {
    public:
        explicit LMShortTraversal7(DataHolder *dh) :
                LMShortTraversal2(SHORT_TRAVERSAL, "ST7", dh) {
        }

        int run() const override;

    protected:
        int traverse(Document *documentation) const override;
    };

    class LMShortTraversal8 : public LMTraversal7 {
    public:
        explicit LMShortTraversal8(DataHolder *dh) :
                LMTraversal7(SHORT_TRAVERSAL, "ST8", dh) {
        }

        int run() const override;

    protected:
        void performOperationOnAssembly(Assembly *assembly) const override;
    };

    class LMShortTraversal9 : public LMShortTraversal1 {
    protected:
        LMShortTraversal9(enum optype type, const char *name,
                          DataHolder *dh)
                : LMShortTraversal1(type, name, dh) {
        }

    public:
        explicit LMShortTraversal9(DataHolder *dh) :
                LMShortTraversal1(SHORT_TRAVERSAL_RO, "ST9", dh) {
        }

    protected:
        int traverse(CompositePart *cpart) const override;

        int traverse(AtomicPart *apart) const override;

        int traverse(AtomicPart *apart,
                     Set<AtomicPart *> &visitedParts) const;

        virtual int performOperationOnAtomicPart(AtomicPart *apart) const;
    };

    class LMShortTraversal10 : public LMShortTraversal9 {
    public:
        explicit LMShortTraversal10(DataHolder *dh) :
                LMShortTraversal9(SHORT_TRAVERSAL, "ST10", dh) {
        }

        int run() const override;

    protected:
        int performOperationOnAtomicPart(AtomicPart *apart) const override;
    };
}


#endif //STMBENCH_SHORT_TRAVERSAL_OPS_LM_H
