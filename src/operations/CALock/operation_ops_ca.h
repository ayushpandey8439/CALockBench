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
        CAOperation6(DataHolder *dh) : Operation(OPERATION_RO, "OP6", dh) {
        }

        virtual int run(int tid) const;

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
        CAOperation7(DataHolder *dh) : Operation(OPERATION_RO, "OP7", dh) {
        }

        virtual int run(int tid) const;

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
        CAOperation8(DataHolder *dh) : Operation(OPERATION_RO, "OP8", dh) {
        }

        virtual int run(int tid) const;

    protected:
        virtual int innerRun(int tid) const;

        virtual void performOperationOnComponent(
                CompositePart *comp) const;
    };

    class CAOperation9 : public CAQuery1 {
    public:
        CAOperation9(DataHolder *dh) : CAQuery1(OPERATION, "OP9", dh) {
        }

        virtual int run(int tid) const;

    protected:
        virtual void performOperationOnAtomicPart(
                AtomicPart *apart) const;
    };

    class CAOperation10 : public CAQuery2 {
    public:
        CAOperation10(DataHolder *dh) : CAQuery2(dh, OPERATION, "OP10", 1) {
        }

        virtual int run(int tid) const;

    protected:
        virtual void performOperationOnAtomicPart(
                AtomicPart *apart) const;
    };

    class CAOperation11 : public CATraversal8 {
    public:
        CAOperation11(DataHolder *dh) : CATraversal8(OPERATION, "OP11", dh) {
        }

        virtual int run(int tid) const;

    protected:
        virtual int traverse(Manual *manual) const;
    };

    class CAOperation12 : public CAOperation6 {
    protected:
        CAOperation12(optype t, const char *n, DataHolder *dh)
                : CAOperation6(t, n, dh) {
        }

    public:
        CAOperation12(DataHolder *dh) : CAOperation6(OPERATION, "OP12", dh) {
        }

        virtual int run(int tid) const;

    protected:
        virtual void performOperationOnComplexAssembly(
                ComplexAssembly *cassm) const;
    };

    class CAOperation13 : public CAOperation7 {
    public:
        CAOperation13(DataHolder *dh) : CAOperation7(OPERATION, "OP13", dh) {
        }

        virtual int run(int tid) const;

    protected:
        virtual void performOperationOnBaseAssembly(
                BaseAssembly *bassm) const;
    };

    class CAOperation14 : public CAOperation8 {
    public:
        CAOperation14(DataHolder *dh) : CAOperation8(OPERATION, "OP14", dh) {
        }

        virtual int run(int tid) const;

    protected:
        virtual void performOperationOnComponent(
                CompositePart *comp) const;
    };

    class CAOperation15 : public CAQuery1 {
    public:
        CAOperation15(DataHolder *dh) : CAQuery1(OPERATION, "OP15", dh) {
        }

        virtual int run(int tid) const;

    protected:
        virtual void performOperationOnAtomicPart(
                AtomicPart *apart) const;
    };

}


#endif //STMBENCH_OPERATION_OPS_CA_H
