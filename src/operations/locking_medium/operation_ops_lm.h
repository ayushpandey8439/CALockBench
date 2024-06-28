#ifndef SB7_LM_OPERATION_OPS_H_
#define SB7_LM_OPERATION_OPS_H_

#include "../operations.h"
#include "query_ops_lm.h"
#include "traversal_ops_lm.h"

namespace sb7 {

    class LMOperation6 : public Operation {
    protected:
        LMOperation6(optype t, const char *n, DataHolder *dh)
                : Operation(t, n, dh) {
        }

    public:
        LMOperation6(DataHolder *dh) : Operation(OPERATION_RO, "OP6", dh) {
        }

        int run(int tid) const override;

    protected:
        int processComplexAssembly(ComplexAssembly *cassm) const;

        virtual int processComplexAssemblyWrap(
                ComplexAssembly *cassm) const;

        virtual void performOperationOnComplexAssembly(
                ComplexAssembly *cassm) const;
    };

    class LMOperation7 : public Operation {
    protected:
        LMOperation7(optype t, const char *n, DataHolder *dh)
                : Operation(t, n, dh) {
        }

    public:
        LMOperation7(DataHolder *dh) : Operation(OPERATION_RO, "OP7", dh) {
        }

        int run(int tid) const override;

    protected:
        int innerRun() const;

        virtual void performOperationOnBaseAssembly(
                BaseAssembly *bassm) const;
    };

    class LMOperation8 : public Operation {
    protected:
        LMOperation8(optype t, const char *n, DataHolder *dh)
                : Operation(t, n, dh) {
        }

    public:
        LMOperation8(DataHolder *dh) : Operation(OPERATION_RO, "OP8", dh) {
        }

        int run(int tid) const override;

    protected:
        int innerRun() const;

        virtual void performOperationOnComponent(
                CompositePart *comp) const;
    };

    class LMOperation9 : public LMQuery1 {
    public:
        LMOperation9(DataHolder *dh) : LMQuery1(OPERATION, "OP9", dh) {
        }

        int run(int tid) const override;

    protected:
        void performOperationOnAtomicPart(
                AtomicPart *apart) const  override;
    };

    class LMOperation10 : public LMQuery2 {
    public:
        LMOperation10(DataHolder *dh) : LMQuery2(dh, OPERATION, "OP10", 1) {
        }

        int run(int tid) const override;

    protected:
        void performOperationOnAtomicPart(
                AtomicPart *apart) const  override;
    };

    class LMOperation11 : public LMTraversal8 {
    public:
        LMOperation11(DataHolder *dh) : LMTraversal8(OPERATION, "OP11", dh) {
        }

        int run(int tid) const override;

    protected:
        int traverse(Manual *manual) const  override;
    };

    class LMOperation12 : public LMOperation6 {
    protected:
        LMOperation12(optype t, const char *n, DataHolder *dh)
                : LMOperation6(t, n, dh) {
        }

    public:
        LMOperation12(DataHolder *dh) : LMOperation6(OPERATION, "OP12", dh) {
        }

    protected:
        virtual int processComplexAssemblyWrap(
                ComplexAssembly *cassm) const;

        virtual void performOperationOnComplexAssembly(
                ComplexAssembly *cassm) const;
    };

    class LMOperation13 : public LMOperation7 {
    public:
        LMOperation13(DataHolder *dh) : LMOperation7(OPERATION, "OP13", dh) {
        }

        int run(int tid) const override;

    protected:
        void performOperationOnBaseAssembly(
                BaseAssembly *bassm) const override;
    };

    class LMOperation14 : public LMOperation8 {
    public:
        LMOperation14(DataHolder *dh) : LMOperation8(OPERATION, "OP14", dh) {
        }

        int run(int tid) const override;

    protected:
        void performOperationOnComponent(
                CompositePart *comp) const override;
    };

    class LMOperation15 : public LMQuery1 {
    public:
        LMOperation15(DataHolder *dh) : LMQuery1(OPERATION, "OP15", dh) {
        }

        int run(int tid) const override;

    protected:
        void performOperationOnAtomicPart(
                AtomicPart *apart) const override;
    };

}

#endif // SB7_LM_OPERATION_OPS_H_
