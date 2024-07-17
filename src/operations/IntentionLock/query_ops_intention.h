#ifndef SB7_Intention_QUERY_OPS_
#define SB7_Intention_QUERY_OPS_

#include "../operations.h"

namespace sb7 {

    class IntentionQuery1 : public Operation {
    protected:
        IntentionQuery1(optype t, const char *n, DataHolder *dh)
                : Operation(t, n, dh) {
        }

    public:
        IntentionQuery1(DataHolder *dh) : Operation(OPERATION_RO, "Q1", dh) {
        }

        int run(int tid) const override;

    protected:
        int innerRun(int tid) const;

        virtual void performOperationOnAtomicPart(AtomicPart *apart) const;
    };

    class IntentionQuery2 : public Operation {
    public:
        IntentionQuery2(DataHolder *dh, optype t = OPERATION_RO,
                  const char *n = "Q2", int percent = 1);

        int run(int tid) const override;

    protected:
        int innerRun(int tid) const;

        virtual void performOperationOnAtomicPart(AtomicPart *apart) const;

    private:
        int percent;
        int maxAtomicDate;
        int minAtomicDate;
    };

    class IntentionQuery3 : public IntentionQuery2 {
    public:
        IntentionQuery3(DataHolder *dh) : IntentionQuery2(dh, OPERATION_RO, "Q3", 10) {
        }
    };

    class IntentionQuery4 : public Operation {
    public:
        IntentionQuery4(DataHolder *dh) : Operation(SHORT_TRAVERSAL_RO, "Q4", dh) {
        }

        int run(int tid) const override;
    };

    class IntentionQuery5 : public Operation {
    protected:
        IntentionQuery5(optype t, const char *n, DataHolder *dh)
                : Operation(t, n, dh) {
        }

    public:
        IntentionQuery5(DataHolder *dh) : Operation(SHORT_TRAVERSAL_RO, "Q5", dh) {
        }

        int run(int tid) const override;

    protected:
        int checkBaseAssembly(BaseAssembly *bassm) const;
    };

    class IntentionQuery6 : public IntentionQuery5 {
    public:
        IntentionQuery6(DataHolder *dh) : IntentionQuery5(TRAVERSAL_RO, "Q6", dh) {
        }

        int run(int tid) const override;

    protected:
        int checkAssembly(Assembly *assembly) const;

        int checkComplexAssembly(ComplexAssembly *assembly) const;
    };

    class IntentionQuery7 : public Operation {
    public:
        IntentionQuery7(DataHolder *dh) : Operation(TRAVERSAL_RO, "Q7", dh) {
        }

        int run(int tid) const override;
    };
}

#endif // SB7_Intention_QUERY_OPS_
