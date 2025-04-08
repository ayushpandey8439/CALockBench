#ifndef SB7_Flexi_OPERATION_OPS_H_
#define SB7_Flexi_OPERATION_OPS_H_

#include "../operations.h"
#include "query_ops_flexi.h"
#include "traversal_ops_flexi.h"

namespace sb7 {

    class FlexiOperation6 : public Operation {
    protected:
        FlexiOperation6(optype t, const char *n, DataHolder *dh)
                : Operation(t, n, dh) {
        }

    public:
        FlexiOperation6(DataHolder *dh) : Operation(OPERATION_RO, "OP6", dh) {
        }

        int run(int tid) const override;

    protected:
        virtual int innerRun(int tid) const;

        virtual void performOperationOnComplexAssembly(
                ComplexAssembly *cassm) const;
    };

    class FlexiOperation7 : public Operation {
    protected:
        FlexiOperation7(optype t, const char *n, DataHolder *dh)
                : Operation(t, n, dh) {
        }

    public:
        FlexiOperation7(DataHolder *dh) : Operation(OPERATION_RO, "OP7", dh) {
        }

        int run(int tid) const override;

    protected:
        virtual int innerRun(int tid) const;

        virtual void performOperationOnBaseAssembly(
                BaseAssembly *bassm) const;
    };

    class FlexiOperation8 : public Operation {
    protected:
        FlexiOperation8(optype t, const char *n, DataHolder *dh)
                : Operation(t, n, dh) {
        }

    public:
        FlexiOperation8(DataHolder *dh) : Operation(OPERATION_RO, "OP8", dh) {
        }

        int run(int tid) const override;

    protected:
        virtual int innerRun(int tid) const;

        virtual void performOperationOnComponent(
                CompositePart *comp) const;
    };

    class FlexiOperation9 : public FlexiQuery1 {
    public:
        FlexiOperation9(DataHolder *dh) : FlexiQuery1(OPERATION, "OP9", dh) {
        }

        int run(int tid) const override;

    protected:
        virtual void performOperationOnAtomicPart(
                AtomicPart *apart) const;
    };

    class FlexiOperation10 : public FlexiQuery2 {
    public:
        FlexiOperation10(DataHolder *dh) : FlexiQuery2(dh, OPERATION, "OP10", 1) {
        }

        int run(int tid) const override;

    protected:
        virtual void performOperationOnAtomicPart(
                AtomicPart *apart) const;
    };

    class FlexiOperation11 : public FlexiTraversal8 {
    public:
        FlexiOperation11(DataHolder *dh) : FlexiTraversal8(OPERATION, "OP11", dh) {
        }

        virtual int run(int tid) const override;

    protected:
        virtual int traverse(Manual *manual) const override;
    };

    class FlexiOperation12 : public FlexiOperation6 {
    protected:
        FlexiOperation12(optype t, const char *n, DataHolder *dh)
                : FlexiOperation6(t, n, dh) {
        }

    public:
        FlexiOperation12(DataHolder *dh) : FlexiOperation6(OPERATION, "OP12", dh) {
        }

        int run(int tid) const override;

    protected:
        void performOperationOnComplexAssembly(
                ComplexAssembly *cassm) const override;
    };

    class FlexiOperation13 : public FlexiOperation7 {
    public:
        FlexiOperation13(DataHolder *dh) : FlexiOperation7(OPERATION, "OP13", dh) {
        }

        int run(int tid) const override;

    protected:
        virtual void performOperationOnBaseAssembly(
                BaseAssembly *bassm) const override;
    };

    class FlexiOperation14 : public FlexiOperation8 {
    public:
        FlexiOperation14(DataHolder *dh) : FlexiOperation8(OPERATION, "OP14", dh) {
        }

        int run(int tid) const override;

    protected:
        void performOperationOnComponent(
                CompositePart *comp) const override;
    };

    class FlexiOperation15 : public FlexiQuery1 {
    public:
        FlexiOperation15(DataHolder *dh) : FlexiQuery1(OPERATION, "OP15", dh) {
        }

        int run(int tid) const override;

    protected:
        void performOperationOnAtomicPart(
                AtomicPart *apart) const;
    };

}

#endif // SB7_Flexi_OPERATION_OPS_H_
