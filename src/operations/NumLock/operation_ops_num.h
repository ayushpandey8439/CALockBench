#ifndef SB7_Num_OPERATION_OPS_H_
#define SB7_Num_OPERATION_OPS_H_

#include "../operations.h"
#include "query_ops_num.h"
#include "traversal_ops_num.h"

namespace sb7 {

    class NumOperation6 : public Operation {
    protected:
        NumOperation6(optype t, const char *n, DataHolder *dh)
                : Operation(t, n, dh) {
        }

    public:
        NumOperation6(DataHolder *dh) : Operation(OPERATION_RO, "OP6", dh) {
        }

        virtual int run(int tid) const;

    protected:
        virtual int innerRun(int tid) const;

        virtual void performOperationOnComplexAssembly(
                ComplexAssembly *cassm) const;
    };

    class NumOperation7 : public Operation {
    protected:
        NumOperation7(optype t, const char *n, DataHolder *dh)
                : Operation(t, n, dh) {
        }

    public:
        NumOperation7(DataHolder *dh) : Operation(OPERATION_RO, "OP7", dh) {
        }

        virtual int run(int tid) const;

    protected:
        virtual int innerRun(int tid) const;

        virtual void performOperationOnBaseAssembly(
                BaseAssembly *bassm) const;
    };

    class NumOperation8 : public Operation {
    protected:
        NumOperation8(optype t, const char *n, DataHolder *dh)
                : Operation(t, n, dh) {
        }

    public:
        NumOperation8(DataHolder *dh) : Operation(OPERATION_RO, "OP8", dh) {
        }

        virtual int run(int tid) const;

    protected:
        virtual int innerRun(int tid) const;

        virtual void performOperationOnComponent(
                CompositePart *comp) const;
    };

    class NumOperation9 : public NumQuery1 {
    public:
        NumOperation9(DataHolder *dh) : NumQuery1(OPERATION, "OP9", dh) {
        }

        virtual int run(int tid) const;

    protected:
        virtual void performOperationOnAtomicPart(
                AtomicPart *apart) const;
    };

    class NumOperation10 : public NumQuery2 {
    public:
        NumOperation10(DataHolder *dh) : NumQuery2(dh, OPERATION, "OP10", 1) {
        }

        virtual int run(int tid) const;

    protected:
        virtual void performOperationOnAtomicPart(
                AtomicPart *apart) const;
    };

    class NumOperation11 : public NumTraversal8 {
    public:
        NumOperation11(DataHolder *dh) : NumTraversal8(OPERATION, "OP11", dh) {
        }

        virtual int run(int tid) const;

    protected:
        virtual int traverse(Manual *manual) const;
    };

    class NumOperation12 : public NumOperation6 {
    protected:
        NumOperation12(optype t, const char *n, DataHolder *dh)
                : NumOperation6(t, n, dh) {
        }

    public:
        NumOperation12(DataHolder *dh) : NumOperation6(OPERATION, "OP12", dh) {
        }

        virtual int run(int tid) const;

    protected:
        virtual void performOperationOnComplexAssembly(
                ComplexAssembly *cassm) const;
    };

    class NumOperation13 : public NumOperation7 {
    public:
        NumOperation13(DataHolder *dh) : NumOperation7(OPERATION, "OP13", dh) {
        }

        virtual int run(int tid) const;

    protected:
        virtual void performOperationOnBaseAssembly(
                BaseAssembly *bassm) const;
    };

    class NumOperation14 : public NumOperation8 {
    public:
        NumOperation14(DataHolder *dh) : NumOperation8(OPERATION, "OP14", dh) {
        }

        virtual int run(int tid) const;

    protected:
        virtual void performOperationOnComponent(
                CompositePart *comp) const;
    };

    class NumOperation15 : public NumQuery1 {
    public:
        NumOperation15(DataHolder *dh) : NumQuery1(OPERATION, "OP15", dh) {
        }

        virtual int run(int tid) const;

    protected:
        virtual void performOperationOnAtomicPart(
                AtomicPart *apart) const;
    };

}

#endif // SB7_Num_OPERATION_OPS_H_
