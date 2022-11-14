//
// Created by Ayush Pandey on 15/11/2022.
//

#ifndef STMBENCH_QUERY_OPS_LM_H
#define STMBENCH_QUERY_OPS_LM_H


#include "../operations.h"

namespace sb7 {

    class LMQuery1 : public Operation {
    protected:
        LMQuery1(optype t, const char *n, DataHolder *dh)
                : Operation(t, n, dh) {
        }

    public:
        explicit LMQuery1(DataHolder *dh) : Operation(OPERATION_RO, "Q1", dh) {
        }

        int run() const override;

    protected:
        int innerRun() const;

        virtual void performOperationOnAtomicPart(AtomicPart *apart) const;
    };

    class LMQuery2 : public Operation {
    public:
        explicit LMQuery2(DataHolder *dh, optype t = OPERATION_RO,
                 const char *n = "Q2", int percent = 1);

        int run() const override;

    protected:
        int innerRun() const;

        virtual void performOperationOnAtomicPart(AtomicPart *apart) const;

    private:
        int maxAtomicDate;
        int minAtomicDate;
    };

    class LMQuery3 : public LMQuery2 {
    public:
        explicit LMQuery3(DataHolder *dh) : LMQuery2(dh, OPERATION_RO, "Q3", 10) {
        }
    };

    class LMQuery4 : public Operation {
    public:
        explicit LMQuery4(DataHolder *dh) : Operation(SHORT_TRAVERSAL_RO, "Q4", dh) {
        }

        int run() const override;
    };

    class LMQuery5 : public Operation {
    protected:
        LMQuery5(optype t, const char *n, DataHolder *dh)
                : Operation(t, n, dh) {
        }

    public:
        explicit LMQuery5(DataHolder *dh) : Operation(SHORT_TRAVERSAL_RO, "Q5", dh) {
        }

        int run() const override;

    protected:
        static int checkBaseAssembly(BaseAssembly *bassm) ;
    };

    class LMQuery6 : public LMQuery5 {
    public:
        explicit LMQuery6(DataHolder *dh) : LMQuery5(TRAVERSAL_RO, "Q6", dh) {
        }

        int run() const override;

    protected:
        int checkAssembly(Assembly *assembly) const;

        int checkComplexAssembly(ComplexAssembly *assembly) const;
    };

    class LMQuery7 : public Operation {
    public:
        explicit LMQuery7(DataHolder *dh) : Operation(TRAVERSAL_RO, "Q7", dh) {
        }

        int run() const override;
    };
}


#endif //STMBENCH_QUERY_OPS_LM_H
