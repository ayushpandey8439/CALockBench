#ifndef SB7_Flexi_QUERY_OPS_
#define SB7_Flexi_QUERY_OPS_

#include "../operations.h"

namespace sb7
{
    class FlexiQuery1 : public Operation
    {
    protected:
        FlexiQuery1(optype t, const char* n, DataHolder* dh)
            : Operation(t, n, dh)
        {
        }

    public:
        FlexiQuery1(DataHolder* dh) : Operation(OPERATION_RO, "Q1", dh)
        {
        }

        int run(int tid) const override;

    protected:
        int innerRun(int tid) const;

        void performOperationOnAtomicPart(AtomicPart* apart) const;
    };

    class FlexiQuery2 : public Operation
    {
    public:
        FlexiQuery2(DataHolder* dh, optype t = OPERATION_RO,
                    const char* n = "Q2", int percent = 1);

        int run(int tid) const override;

    protected:
        int innerRun(int tid) const;

        void performOperationOnAtomicPart(AtomicPart* apart) const;

    private:
        int percent;
        int maxAtomicDate;
        int minAtomicDate;
    };

    class FlexiQuery3 : public FlexiQuery2
    {
    public:
        FlexiQuery3(DataHolder* dh) : FlexiQuery2(dh, OPERATION_RO, "Q3", 10)
        {
        }
    };

    class FlexiQuery4 : public Operation
    {
    public:
        FlexiQuery4(DataHolder* dh) : Operation(SHORT_TRAVERSAL_RO, "Q4", dh)
        {
        }

        int run(int tid) const override;
    };

    class FlexiQuery5 : public Operation
    {
    protected:
        FlexiQuery5(optype t, const char* n, DataHolder* dh)
            : Operation(t, n, dh)
        {
        }

    public:
        FlexiQuery5(DataHolder* dh) : Operation(SHORT_TRAVERSAL_RO, "Q5", dh)
        {
        }

        int run(int tid) const override;

    protected:
        int checkBaseAssembly(BaseAssembly* bassm) const;
    };

    class FlexiQuery6 : public FlexiQuery5
    {
    public:
        FlexiQuery6(DataHolder* dh) : FlexiQuery5(TRAVERSAL_RO, "Q6", dh)
        {
        }

        int run(int tid) const override;

    protected:
        int checkAssembly(Assembly* assembly) const;

        int checkComplexAssembly(ComplexAssembly* assembly) const;
    };

    class FlexiQuery7 : public Operation
    {
    public:
        FlexiQuery7(DataHolder* dh) : Operation(TRAVERSAL_RO, "Q7", dh)
        {
        }

        int run(int tid) const override;
    };
}

#endif // SB7_Flexi_QUERY_OPS_
