#ifndef SB7_LC_OPERATION_OPS_H_
#define SB7_LC_OPERATION_OPS_H_

#include "../operations.h"
#include "query_ops_lc.h"
#include "traversal_ops_lc.h"

namespace sb7 {

    class LCOperation6 : public Operation {
    protected:
        LCOperation6(optype t, const char *n, DataHolder *dh)
                : Operation(t, n, dh) {
        }

    public:
        LCOperation6(DataHolder *dh) : Operation(OPERATION_RO, "OP6", dh) {
        }

        int run(int tid) const override;

    protected:
        int innerRun() const;

        virtual void performOperationOnComplexAssembly(
                ComplexAssembly *cassm) const;
    };

    class LCOperation7 : public Operation {
    protected:
        LCOperation7(optype t, const char *n, DataHolder *dh)
                : Operation(t, n, dh) {
        }

    public:
        LCOperation7(DataHolder *dh) : Operation(OPERATION_RO, "OP7", dh) {
        }

        int run(int tid) const override;

    protected:
        virtual int innerRun() const;

        virtual void performOperationOnBaseAssembly(
                BaseAssembly *bassm) const;
    };

    class LCOperation8 : public Operation {
    protected:
        LCOperation8(optype t, const char *n, DataHolder *dh)
                : Operation(t, n, dh) {
        }

    public:
        LCOperation8(DataHolder *dh) : Operation(OPERATION_RO, "OP8", dh) {
        }

        int run(int tid) const override;

    protected:
        virtual int innerRun() const;

        virtual void performOperationOnComponent(
                CompositePart *comp) const;
    };

    class LCOperation9 : public LCQuery1 {
    public:
        LCOperation9(DataHolder *dh) : LCQuery1(OPERATION, "OP9", dh) {
        }

        int run(int tid) const override;

    protected:
        void performOperationOnAtomicPart(
                AtomicPart *apart) const override;
    };

    class LCOperation10 : public LCQuery2 {
    public:
        LCOperation10(DataHolder *dh) : LCQuery2(dh, OPERATION, "OP10", 1) {
        }

        int run(int tid) const override;

    protected:
        void performOperationOnAtomicPart(
                AtomicPart *apart) const override;
    };

    class LCOperation11 : public LCTraversal8 {
    public:
        LCOperation11(DataHolder *dh) : LCTraversal8(OPERATION, "OP11", dh) {
        }

        int run(int tid) const override;

    protected:
        int traverse(Manual *manual) const override;
    };

    class LCOperation12 : public LCOperation6 {
    protected:
        LCOperation12(optype t, const char *n, DataHolder *dh)
                : LCOperation6(t, n, dh) {
        }

    public:
        LCOperation12(DataHolder *dh) : LCOperation6(OPERATION, "OP12", dh) {
        }

        int run(int tid) const override;

    protected:
        void performOperationOnComplexAssembly(
                ComplexAssembly *cassm) const override;
    };

    class LCOperation13 : public LCOperation7 {
    public:
        LCOperation13(DataHolder *dh) : LCOperation7(OPERATION, "OP13", dh) {
        }

        int run(int tid) const override;

    protected:
        void performOperationOnBaseAssembly(
                BaseAssembly *bassm) const override;
    };

    class LCOperation14 : public LCOperation8 {
    public:
        LCOperation14(DataHolder *dh) : LCOperation8(OPERATION, "OP14", dh) {
        }

        int run(int tid) const override;

    protected:
        void performOperationOnComponent(
                CompositePart *comp) const override;
    };

    class LCOperation15 : public LCQuery1 {
    public:
        LCOperation15(DataHolder *dh) : LCQuery1(OPERATION, "OP15", dh) {
        }

        int run(int tid) const override;

    protected:
        void performOperationOnAtomicPart(
                AtomicPart *apart) const override;
    };

}

#endif // SB7_LC_OPERATION_OPS_H_
