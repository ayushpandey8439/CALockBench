#ifndef SB7_Mid_QUERY_OPS_
#define SB7_Mid_QUERY_OPS_

#include "../operations.h"

namespace sb7 {

    class MidQuery1 : public Operation {
    protected:
        MidQuery1(optype t, const char *n, DataHolder *dh)
                : Operation(t, n, dh) {
        }

    public:
        MidQuery1(DataHolder *dh) : Operation(OPERATION_RO, "Q1", dh) {
        }

        virtual int run(int tid) const;

    protected:
        int innerRun(int tid) const;

        virtual void performOperationOnAtomicPart(AtomicPart *apart) const;
    };

    class MidQuery2 : public Operation {
    public:
        MidQuery2(DataHolder *dh, optype t = OPERATION_RO,
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

    class MidQuery3 : public MidQuery2 {
    public:
        MidQuery3(DataHolder *dh) : MidQuery2(dh, OPERATION_RO, "Q3", 10) {
        }
    };

    class MidQuery4 : public Operation {
    public:
        MidQuery4(DataHolder *dh) : Operation(SHORT_TRAVERSAL_RO, "Q4", dh) {
        }

        virtual int run(int tid) const;
    };

    class MidQuery5 : public Operation {
    protected:
        MidQuery5(optype t, const char *n, DataHolder *dh)
                : Operation(t, n, dh) {
        }

    public:
        MidQuery5(DataHolder *dh) : Operation(SHORT_TRAVERSAL_RO, "Q5", dh) {
        }

        virtual int run(int tid) const;

    protected:
        int checkBaseAssembly(BaseAssembly *bassm) const;
    };

    class MidQuery6 : public MidQuery5 {
    public:
        MidQuery6(DataHolder *dh) : MidQuery5(TRAVERSAL_RO, "Q6", dh) {
        }

        virtual int run(int tid) const;

    protected:
        int checkAssembly(Assembly *assembly) const;

        int checkComplexAssembly(ComplexAssembly *assembly) const;
    };

    class MidQuery7 : public Operation {
    public:
        MidQuery7(DataHolder *dh) : Operation(TRAVERSAL_RO, "Q7", dh) {
        }

        virtual int run(int tid) const;
    };
}

#endif // SB7_Mid_QUERY_OPS_
