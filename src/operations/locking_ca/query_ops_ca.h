//
// Created by Ayush Pandey on 15/11/2022.
//

#ifndef STMBENCH_QUERY_OPS_CA_H
#define STMBENCH_QUERY_OPS_CA_H


#include "../operations.h"

namespace sb7 {

    class CAQuery1 : public Operation {
    protected:
        CAQuery1(optype t, const char *n, DataHolder *dh)
                : Operation(t, n, dh) {
        }

    public:
        explicit CAQuery1(DataHolder *dh) : Operation(OPERATION_RO, "Q1", dh) {
        }

        int run(int tid) const override;

    protected:
        int innerRun(int tid) const;

        virtual void performOperationOnAtomicPart(AtomicPart *apart) const;
    };

    class CAQuery2 : public Operation {
    public:
        explicit CAQuery2(DataHolder *dh, optype t = OPERATION_RO,
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

    class CAQuery3 : public CAQuery2 {
    public:
        explicit CAQuery3(DataHolder *dh) : CAQuery2(dh, OPERATION_RO, "Q3", 10) {
        }
    };

    class CAQuery4 : public Operation {
    public:
        explicit CAQuery4(DataHolder *dh) : Operation(SHORT_TRAVERSAL_RO, "Q4", dh) {
        }

        int run(int tid) const override;
    };

    class CAQuery5 : public Operation {
    protected:
        CAQuery5(optype t, const char *n, DataHolder *dh)
                : Operation(t, n, dh) {
        }

    public:
        explicit CAQuery5(DataHolder *dh) : Operation(SHORT_TRAVERSAL_RO, "Q5", dh) {
        }

        int run(int tid) const override;

    protected:
        static int checkBaseAssembly(BaseAssembly *bassm) ;
    };

    class CAQuery6 : public CAQuery5 {
    public:
        explicit CAQuery6(DataHolder *dh) : CAQuery5(TRAVERSAL_RO, "Q6", dh) {
        }

        int run(int tid) const override;

    protected:
        int checkAssembly(Assembly *assembly) const;

        int checkComplexAssembly(ComplexAssembly *assembly) const;
    };

    class CAQuery7 : public Operation {
    public:
        explicit CAQuery7(DataHolder *dh) : Operation(TRAVERSAL_RO, "Q7", dh) {
        }

        int run(int tid) const override;
    };
}

#endif //STMBENCH_QUERY_OPS_CA_H
