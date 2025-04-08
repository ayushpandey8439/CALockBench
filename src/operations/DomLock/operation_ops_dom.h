#ifndef SB7_Dom_OPERATION_OPS_H_
#define SB7_Dom_OPERATION_OPS_H_

#include "../operations.h"
#include "query_ops_dom.h"
#include "traversal_ops_dom.h"

namespace sb7
{
    class DomOperation6 : public Operation
    {
    protected:
        DomOperation6(optype t, const char* n, DataHolder* dh)
            : Operation(t, n, dh)
        {
        }

    public:
        explicit DomOperation6(DataHolder* dh) : Operation(OPERATION_RO, "OP6", dh)
        {
        }

        int run(int tid) const override;

    protected:
        virtual int innerRun(int tid) const;

        virtual void performOperationOnComplexAssembly(
            ComplexAssembly* cassm) const;
    };

    class DomOperation7 : public Operation
    {
    protected:
        DomOperation7(optype t, const char* n, DataHolder* dh)
            : Operation(t, n, dh)
        {
        }

    public:
        explicit DomOperation7(DataHolder* dh) : Operation(OPERATION_RO, "OP7", dh)
        {
        }

        int run(int tid) const override;

    protected:
        virtual int innerRun(int tid) const;

        virtual void performOperationOnBaseAssembly(
            BaseAssembly* bassm) const;
    };

    class DomOperation8 : public Operation
    {
    protected:
        DomOperation8(optype t, const char* n, DataHolder* dh)
            : Operation(t, n, dh)
        {
        }

    public:
        explicit DomOperation8(DataHolder* dh) : Operation(OPERATION_RO, "OP8", dh)
        {
        }

        int run(int tid) const override;

    protected:
        virtual int innerRun(int tid) const;

        virtual void performOperationOnComponent(
            CompositePart* comp) const;
    };

    class DomOperation9 : public DomQuery1
    {
    public:
        explicit DomOperation9(DataHolder* dh) : DomQuery1(OPERATION, "OP9", dh)
        {
        }

        int run(int tid) const override;

    protected:
        void performOperationOnAtomicPart(
            AtomicPart* apart) const override;
    };

    class DomOperation10 : public DomQuery2
    {
    public:
        explicit DomOperation10(DataHolder* dh) : DomQuery2(dh, OPERATION, "OP10", 1)
        {
        }

        int run(int tid) const override;

    protected:
        void performOperationOnAtomicPart(
            AtomicPart* apart) const override;
    };

    class DomOperation11 : public DomTraversal8
    {
    public:
        explicit DomOperation11(DataHolder* dh) : DomTraversal8(OPERATION, "OP11", dh)
        {
        }

        int run(int tid) const override;

    protected:
        int traverse(Manual* manual) const override;
    };

    class DomOperation12 : public DomOperation6
    {
    protected:
        DomOperation12(optype t, const char* n, DataHolder* dh)
            : DomOperation6(t, n, dh)
        {
        }

    public:
        explicit DomOperation12(DataHolder* dh) : DomOperation6(OPERATION, "OP12", dh)
        {
        }

        int run(int tid) const override;

    protected:
        void performOperationOnComplexAssembly(
            ComplexAssembly* cassm) const override;
    };

    class DomOperation13 : public DomOperation7
    {
    public:
        explicit DomOperation13(DataHolder* dh) : DomOperation7(OPERATION, "OP13", dh)
        {
        }

        int run(int tid) const override;

    protected:
        void performOperationOnBaseAssembly(
            BaseAssembly* bassm) const override;
    };

    class DomOperation14 : public DomOperation8
    {
    public:
        explicit DomOperation14(DataHolder* dh) : DomOperation8(OPERATION, "OP14", dh)
        {
        }

        int run(int tid) const override;

    protected:
        void performOperationOnComponent(
            CompositePart* comp) const override;
    };

    class DomOperation15 : public DomQuery1
    {
    public:
        explicit DomOperation15(DataHolder* dh) : DomQuery1(OPERATION, "OP15", dh)
        {
        }

        int run(int tid) const override;

    protected:
        void performOperationOnAtomicPart(
            AtomicPart* apart) const override;
    };
}

#endif // SB7_Dom_OPERATION_OPS_H_
