#ifndef SB7_Num_QUERY_OPS_
#define SB7_Num_QUERY_OPS_

#include "../operations.h"

namespace sb7 {

    class NumQuery1 : public Operation {
    protected:
        NumQuery1(optype t, const char *n, DataHolder *dh)
                : Operation(t, n, dh) {
        }

    public:
        NumQuery1(DataHolder *dh) : Operation(OPERATION_RO, "Q1", dh) {
        }

        virtual int run(int tid) const;

    protected:
        int innerRun(int tid) const;

        virtual void performOperationOnAtomicPart(AtomicPart *apart) const;
    };

    class NumQuery2 : public Operation {
    public:
        NumQuery2(DataHolder *dh, optype t = OPERATION_RO,
                  const char *n = "Q2", int percent = 1);

        virtual int run(int tid) const;

    protected:
        int innerRun(int tid) const;

        virtual void performOperationOnAtomicPart(AtomicPart *apart) const;

    private:
        int percent;
        int maxAtomicDate;
        int minAtomicDate;
    };

    class NumQuery3 : public NumQuery2 {
    public:
        NumQuery3(DataHolder *dh) : NumQuery2(dh, OPERATION_RO, "Q3", 10) {
        }
    };

    class NumQuery4 : public Operation {
    public:
        NumQuery4(DataHolder *dh) : Operation(SHORT_TRAVERSAL_RO, "Q4", dh) {
        }

        virtual int run(int tid) const;
    };

    class NumQuery5 : public Operation {
    protected:
        NumQuery5(optype t, const char *n, DataHolder *dh)
                : Operation(t, n, dh) {
        }

    public:
        NumQuery5(DataHolder *dh) : Operation(SHORT_TRAVERSAL_RO, "Q5", dh) {
        }

        virtual int run(int tid) const;

    protected:
        int checkBaseAssembly(BaseAssembly *bassm) const;
    };

    class NumQuery6 : public NumQuery5 {
    public:
        NumQuery6(DataHolder *dh) : NumQuery5(TRAVERSAL_RO, "Q6", dh) {
        }

        virtual int run(int tid) const;

    protected:
        int checkAssembly(Assembly *assembly) const;

        int checkComplexAssembly(ComplexAssembly *assembly) const;
    };

    class NumQuery7 : public Operation {
    public:
        NumQuery7(DataHolder *dh) : Operation(TRAVERSAL_RO, "Q7", dh) {
        }

        virtual int run(int tid) const;
    };
}

#endif // SB7_Num_QUERY_OPS_
