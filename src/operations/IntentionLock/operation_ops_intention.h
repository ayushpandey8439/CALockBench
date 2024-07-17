#ifndef SB7_Intention_OPERATION_OPS_H_
#define SB7_Intention_OPERATION_OPS_H_

#include "../operations.h"
#include "query_ops_intention.h"

namespace sb7
{
    class IntentionOperation6 : public Operation
    {
    protected:
        IntentionOperation6(optype t, const char* n, DataHolder* dh)
            : Operation(t, n, dh)
        {
        }

    public:
        explicit IntentionOperation6(DataHolder* dh) : Operation(OPERATION_RO, "OP6", dh)
        {
        }

        int run(int tid) const override;

    protected:
        virtual int innerRun(int tid) const;

        virtual void performOperationOnComplexAssembly(
            ComplexAssembly* cassm) const;
    };

    class IntentionOperation7 : public Operation
    {
    protected:
        IntentionOperation7(optype t, const char* n, DataHolder* dh)
            : Operation(t, n, dh)
        {
        }

    public:
        explicit IntentionOperation7(DataHolder* dh) : Operation(OPERATION_RO, "OP7", dh)
        {
        }

        int run(int tid) const override;

    protected:
        virtual int innerRun(int tid) const;

        virtual void performOperationOnBaseAssembly(
            BaseAssembly* bassm) const;
    };

    class IntentionOperation8 : public Operation
    {
    protected:
        IntentionOperation8(optype t, const char* n, DataHolder* dh)
            : Operation(t, n, dh)
        {
        }

    public:
        explicit IntentionOperation8(DataHolder* dh) : Operation(OPERATION_RO, "OP8", dh)
        {
        }

        int run(int tid) const override;

    protected:
        virtual int innerRun(int tid) const;

        virtual void performOperationOnComponent(
            CompositePart* comp) const;
    };

    class IntentionOperation9 : public IntentionQuery1
    {
    public:
        explicit IntentionOperation9(DataHolder* dh) : IntentionQuery1(OPERATION, "OP9", dh)
        {
        }

        int run(int tid) const override;

    protected:
        void performOperationOnAtomicPart(
            AtomicPart* apart) const override;
    };

    class IntentionOperation10 : public IntentionQuery2
    {
    public:
        explicit IntentionOperation10(DataHolder* dh) : IntentionQuery2(dh, OPERATION, "OP10", 1)
        {
        }

        int run(int tid) const override;

    protected:
        void performOperationOnAtomicPart(
            AtomicPart* apart) const override;
    };
}

#endif // SB7_Intention_OPERATION_OPS_H_
