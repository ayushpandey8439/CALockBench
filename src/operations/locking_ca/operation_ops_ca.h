//
// Created by Ayush Pandey on 15/11/2022.
//

#ifndef STMBENCH_OPERATION_OPS_CA_H
#define STMBENCH_OPERATION_OPS_CA_H



#include "../operations.h"
#include "query_ops_ca.h"
#include "traversal_ops_ca.h"

namespace sb7 {

    class CAOperation6 : public Operation {
    protected:
        CAOperation6(optype t, const char *n, DataHolder *dh)
                : Operation(t, n, dh) {
        }

    public:
        explicit CAOperation6(DataHolder *dh) : Operation(OPERATION_RO, "OP6", dh) {
        }

        int run(int tid) const override;

    protected:
        virtual int innerRun(int tid) const;

        virtual void performOperationOnComplexAssembly(
                ComplexAssembly *cassm) const;
    };

    class CAOperation7 : public Operation {
    protected:
        CAOperation7(optype t, const char *n, DataHolder *dh)
                : Operation(t, n, dh) {
        }

    public:
        explicit CAOperation7(DataHolder *dh) : Operation(OPERATION_RO, "OP7", dh) {
        }

        int run(int tid) const override;

    protected:
        virtual int innerRun(int tid) const;

        virtual void performOperationOnBaseAssembly(
                BaseAssembly *bassm) const;
    };

    class CAOperation8 : public Operation {
    protected:
        CAOperation8(optype t, const char *n, DataHolder *dh)
                : Operation(t, n, dh) {
        }

    public:
        explicit CAOperation8(DataHolder *dh) : Operation(OPERATION_RO, "OP8", dh) {
        }

        int run(int tid) const override;

    protected:
        virtual int innerRun(int tid) const;

        virtual void performOperationOnComponent(
                CompositePart *comp) const;
    };

    class CAOperation9 : public CAQuery1 {
    public:
        explicit CAOperation9(DataHolder *dh) : CAQuery1(OPERATION, "OP9", dh) {
        }

        int run(int tid) const override;

    protected:
        void performOperationOnAtomicPart(
                AtomicPart *apart) const override;
    };

    class CAOperation10 : public CAQuery2 {
    public:
        explicit CAOperation10(DataHolder *dh) : CAQuery2(dh, OPERATION, "OP10", 1) {
        }

        int run(int tid) const override;

    protected:
        void performOperationOnAtomicPart(
                AtomicPart *apart) const override;
    };

    class CAOperation11 : public CATraversal8 {
    public:
        explicit CAOperation11(DataHolder *dh) : CATraversal8(OPERATION, "OP11", dh) {
        }

        int run(int tid) const override;

    protected:
        int traverse(Manual *manual) const override;
    };

    class CAOperation12 : public CAOperation6 {
    protected:
        CAOperation12(optype t, const char *n, DataHolder *dh)
                : CAOperation6(t, n, dh) {
        }

    public:
        explicit CAOperation12(DataHolder *dh) : CAOperation6(OPERATION, "OP12", dh) {
        }

        int run(int tid) const override;

    protected:
        void performOperationOnComplexAssembly(
                ComplexAssembly *cassm) const override;
    };

    class CAOperation13 : public CAOperation7 {
    public:
        explicit CAOperation13(DataHolder *dh) : CAOperation7(OPERATION, "OP13", dh) {
        }

        int run(int tid) const override;

    protected:
        void performOperationOnBaseAssembly(
                BaseAssembly *bassm) const override;
    };

    class CAOperation14 : public CAOperation8 {
    public:
        explicit CAOperation14(DataHolder *dh) : CAOperation8(OPERATION, "OP14", dh) {
        }

        int run(int tid) const override;

    protected:
        void performOperationOnComponent(
                CompositePart *comp) const override;
    };

    class CAOperation15 : public CAQuery1 {
    public:
        explicit CAOperation15(DataHolder *dh) : CAQuery1(OPERATION, "OP15", dh) {
        }

        int run(int tid) const override;

    protected:
        void performOperationOnAtomicPart(
                AtomicPart *apart) const override;
    };

}



#endif //STMBENCH_OPERATION_OPS_CA_H
