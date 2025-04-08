#ifndef SB7_LF_OPERATION_OPS_H_
#define SB7_LF_OPERATION_OPS_H_

#include "../operations.h"
#include "query_ops_lf.h"
#include "traversal_ops_lf.h"

namespace sb7 {

    class LFOperation6 : public Operation {
    protected:
        LFOperation6(optype t, const char *n, DataHolder *dh)
                : Operation(t, n, dh) {
        }

    public:
        LFOperation6(DataHolder *dh) : Operation(OPERATION_RO, "OP6", dh) {
        }

        virtual int run() const;

    protected:
        virtual void performOperationOnComplexAssembly(
                ComplexAssembly *cassm) const;
    };

    class LFOperation7 : public Operation {
    protected:
        LFOperation7(optype t, const char *n, DataHolder *dh)
                : Operation(t, n, dh) {
        }

    public:
        LFOperation7(DataHolder *dh) : Operation(OPERATION_RO, "OP7", dh) {
        }

        virtual int run() const;

    protected:
        virtual void performOperationOnBaseAssembly(
                BaseAssembly *bassm) const;
    };

    class LFOperation8 : public Operation {
    protected:
        LFOperation8(optype t, const char *n, DataHolder *dh)
                : Operation(t, n, dh) {
        }

    public:
        LFOperation8(DataHolder *dh) : Operation(OPERATION_RO, "OP8", dh) {
        }

        virtual int run() const;

    protected:
        virtual void performOperationOnComponent(
                CompositePart *comp) const;
    };

    class LFOperation9 : public LFQuery1 {
    public:
        LFOperation9(DataHolder *dh) : LFQuery1(OPERATION, "OP9", dh) {
        }

    protected:
        virtual void performOperationOnAtomicPart(
                AtomicPart *apart) const;
    };

    class LFOperation10 : public LFQuery2 {
    public:
        LFOperation10(DataHolder *dh) : LFQuery2(dh, OPERATION, "OP10", 1) {
        }

    protected:
        virtual void performOperationOnAtomicPart(
                AtomicPart *apart) const;
    };

    class LFOperation11 : public LFTraversal8 {
    public:
        LFOperation11(DataHolder *dh) : LFTraversal8(OPERATION, "OP11", dh) {
        }

    protected:
        virtual int traverse(Manual *manual) const;
    };

    class LFOperation12 : public LFOperation6 {
    protected:
        LFOperation12(optype t, const char *n, DataHolder *dh)
                : LFOperation6(t, n, dh) {
        }

    public:
        LFOperation12(DataHolder *dh) : LFOperation6(OPERATION, "OP12", dh) {
        }

    protected:
        virtual void performOperationOnComplexAssembly(
                ComplexAssembly *cassm) const;
    };

    class LFOperation13 : public LFOperation7 {
    public:
        LFOperation13(DataHolder *dh) : LFOperation7(OPERATION, "OP13", dh) {
        }

    protected:
        virtual void performOperationOnBaseAssembly(
                BaseAssembly *bassm) const;
    };

    class LFOperation14 : public LFOperation8 {
    public:
        LFOperation14(DataHolder *dh) : LFOperation8(OPERATION, "OP14", dh) {
        }

    protected:
        virtual void performOperationOnComponent(
                CompositePart *comp) const;
    };

    class LFOperation15 : public LFQuery1 {
    public:
        LFOperation15(DataHolder *dh) : LFQuery1(OPERATION, "OP15", dh) {
        }

    protected:
        virtual void performOperationOnAtomicPart(
                AtomicPart *apart) const;
    };

}

#endif // SB7_LF_OPERATION_OPS_H_
