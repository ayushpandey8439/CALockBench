#ifndef SB7_Mid_OPERATION_OPS_H_
#define SB7_Mid_OPERATION_OPS_H_

#include "../operations.h"
#include "query_ops_mid.h"
#include "traversal_ops_mid.h"

namespace sb7 {

    class MidOperation6 : public Operation {
    protected:
        MidOperation6(optype t, const char *n, DataHolder *dh)
                : Operation(t, n, dh) {
        }

    public:
        MidOperation6(DataHolder *dh) : Operation(OPERATION_RO, "OP6", dh) {
        }

        virtual int run(int tid) const;

    protected:
        virtual int innerRun(int tid) const;

        virtual void performOperationOnComplexAssembly(
                ComplexAssembly *cassm) const;
    };

    class MidOperation7 : public Operation {
    protected:
        MidOperation7(optype t, const char *n, DataHolder *dh)
                : Operation(t, n, dh) {
        }

    public:
        MidOperation7(DataHolder *dh) : Operation(OPERATION_RO, "OP7", dh) {
        }

        virtual int run(int tid) const;

    protected:
        virtual int innerRun(int tid) const;

        virtual void performOperationOnBaseAssembly(
                BaseAssembly *bassm) const;
    };

    class MidOperation8 : public Operation {
    protected:
        MidOperation8(optype t, const char *n, DataHolder *dh)
                : Operation(t, n, dh) {
        }

    public:
        MidOperation8(DataHolder *dh) : Operation(OPERATION_RO, "OP8", dh) {
        }

        virtual int run(int tid) const;

    protected:
        virtual int innerRun(int tid) const;

        virtual void performOperationOnComponent(
                CompositePart *comp) const;
    };

    class MidOperation9 : public MidQuery1 {
    public:
        MidOperation9(DataHolder *dh) : MidQuery1(OPERATION, "OP9", dh) {
        }

        virtual int run(int tid) const;

    protected:
        virtual void performOperationOnAtomicPart(
                AtomicPart *apart) const;
    };

    class MidOperation10 : public MidQuery2 {
    public:
        MidOperation10(DataHolder *dh) : MidQuery2(dh, OPERATION, "OP10", 1) {
        }

        virtual int run(int tid) const;

    protected:
        virtual void performOperationOnAtomicPart(
                AtomicPart *apart) const;
    };

    class MidOperation11 : public MidTraversal8 {
    public:
        MidOperation11(DataHolder *dh) : MidTraversal8(OPERATION, "OP11", dh) {
        }

        virtual int run(int tid) const;

    protected:
        virtual int traverse(Manual *manual) const;
    };

    class MidOperation12 : public MidOperation6 {
    protected:
        MidOperation12(optype t, const char *n, DataHolder *dh)
                : MidOperation6(t, n, dh) {
        }

    public:
        MidOperation12(DataHolder *dh) : MidOperation6(OPERATION, "OP12", dh) {
        }

        virtual int run(int tid) const;

    protected:
        virtual void performOperationOnComplexAssembly(
                ComplexAssembly *cassm) const;
    };

    class MidOperation13 : public MidOperation7 {
    public:
        MidOperation13(DataHolder *dh) : MidOperation7(OPERATION, "OP13", dh) {
        }

        virtual int run(int tid) const;

    protected:
        virtual void performOperationOnBaseAssembly(
                BaseAssembly *bassm) const;
    };

    class MidOperation14 : public MidOperation8 {
    public:
        MidOperation14(DataHolder *dh) : MidOperation8(OPERATION, "OP14", dh) {
        }

        virtual int run(int tid) const;

    protected:
        virtual void performOperationOnComponent(
                CompositePart *comp) const;
    };

    class MidOperation15 : public MidQuery1 {
    public:
        MidOperation15(DataHolder *dh) : MidQuery1(OPERATION, "OP15", dh) {
        }

        virtual int run(int tid) const;

    protected:
        virtual void performOperationOnAtomicPart(
                AtomicPart *apart) const;
    };

}

#endif // SB7_Mid_OPERATION_OPS_H_
