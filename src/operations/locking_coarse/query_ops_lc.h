//
// Created by Ayush Pandey on 15/11/2022.
//

#ifndef STMBENCH_QUERY_OPS_LC_H
#define STMBENCH_QUERY_OPS_LC_H


#include "../operations.h"

namespace sb7 {

    class LCQuery1 : public Operation {
    protected:
        LCQuery1(optype t, const char *n, DataHolder *dh)
                : Operation(t, n, dh) {
        }

    public:
        explicit LCQuery1(DataHolder *dh) : Operation(OPERATION_RO, "Q1", dh) {
        }

        int run() const override;

    protected:
        int innerRun() const;

        virtual void performOperationOnAtomicPart(AtomicPart *apart) const;
    };

    class LCQuery2 : public Operation {
    public:
        explicit LCQuery2(DataHolder *dh, optype t = OPERATION_RO,
                 const char *n = "Q2", int percent = 1);

        int run() const override;

    protected:
        int innerRun() const;

        virtual void performOperationOnAtomicPart(AtomicPart *apart) const;

    private:
        int maxAtomicDate;
        int minAtomicDate;
    };

    class LCQuery3 : public LCQuery2 {
    public:
        explicit LCQuery3(DataHolder *dh) : LCQuery2(dh, OPERATION_RO, "Q3", 10) {
        }
    };

    class LCQuery4 : public Operation {
    public:
        explicit LCQuery4(DataHolder *dh) : Operation(SHORT_TRAVERSAL_RO, "Q4", dh) {
        }

        int run() const override;
    };

    class LCQuery5 : public Operation {
    protected:
        LCQuery5(optype t, const char *n, DataHolder *dh)
                : Operation(t, n, dh) {
        }

    public:
        explicit LCQuery5(DataHolder *dh) : Operation(SHORT_TRAVERSAL_RO, "Q5", dh) {
        }

        int run() const override;

    protected:
        static int checkBaseAssembly(BaseAssembly *bassm) ;
    };

    class LCQuery6 : public LCQuery5 {
    public:
        explicit LCQuery6(DataHolder *dh) : LCQuery5(TRAVERSAL_RO, "Q6", dh) {
        }

        int run() const override;

    protected:
        int checkAssembly(Assembly *assembly) const;

        int checkComplexAssembly(ComplexAssembly *assembly) const;
    };

    class LCQuery7 : public Operation {
    public:
        explicit LCQuery7(DataHolder *dh) : Operation(TRAVERSAL_RO, "Q7", dh) {
        }

        int run() const override;
    };
}

#endif //STMBENCH_QUERY_OPS_LC_H
