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
        CAQuery1(DataHolder *dh) : Operation(OPERATION_RO, "Q1", dh) {
        }

        virtual int run(int tid) const;

    protected:
        int innerRun(int tid) const;

        virtual void performOperationOnAtomicPart(AtomicPart *apart) const;
    };

    class CAQuery2 : public Operation {
    public:
        CAQuery2(DataHolder *dh, optype t = OPERATION_RO,
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

    class CAQuery3 : public CAQuery2 {
    public:
        CAQuery3(DataHolder *dh) : CAQuery2(dh, OPERATION_RO, "Q3", 10) {
        }
    };

    class CAQuery4 : public Operation {
    public:
        CAQuery4(DataHolder *dh) : Operation(SHORT_TRAVERSAL_RO, "Q4", dh) {
        }

        virtual int run(int tid) const;
    };

    class CAQuery5 : public Operation {
    protected:
        CAQuery5(optype t, const char *n, DataHolder *dh)
                : Operation(t, n, dh) {
        }

    public:
        CAQuery5(DataHolder *dh) : Operation(SHORT_TRAVERSAL_RO, "Q5", dh) {
        }

        virtual int run(int tid) const;

    protected:
        int checkBaseAssembly(BaseAssembly *bassm) const;
    };

    class CAQuery6 : public CAQuery5 {
    public:
        CAQuery6(DataHolder *dh) : CAQuery5(TRAVERSAL_RO, "Q6", dh) {
        }

        virtual int run(int tid) const;

    protected:
        int checkAssembly(Assembly *assembly) const;

        int checkComplexAssembly(ComplexAssembly *assembly) const;
    };

    class CAQuery7 : public Operation {
    public:
        CAQuery7(DataHolder *dh) : Operation(TRAVERSAL_RO, "Q7", dh) {
        }

        virtual int run(int tid) const;
    };
}

#endif //STMBENCH_QUERY_OPS_CA_H
