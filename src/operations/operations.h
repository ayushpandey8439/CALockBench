#ifndef SB7_OPERATIONS_H
#define SB7_OPERATIONS_H

#include <vector>

#include "../data_holder.h"
#include "../thread/thread.h"

// define number of operation types as it will be required in a few places
//#define OPERATION_TYPE_NUM 7

using namespace std;

namespace sb7 {

    enum optype {
        TRAVERSAL = 0,
        TRAVERSAL_RO,
        SHORT_TRAVERSAL,
        SHORT_TRAVERSAL_RO,
        OPERATION,
        OPERATION_RO,
        STRUCTURAL_MODIFICATION
    };

    struct OperationType {
        OperationType(enum optype ty, const char *n) :
                type(ty),
                count(0),
                probability(0.0),
                success(0),
                aborted(0),
                failure(0),
                maxttc(0),
                name(n) {
        }

        enum optype type;
        int count;
        double probability;
        int success;
        int aborted;
        int failure;
        int maxttc;
        const char *name;
    };

    // abstract class representing operations
    // all operations are stateless
    class Operation {
    public:
        Operation(enum optype ty, const char *n, DataHolder *dh = NULL)
                : type(ty), name(n), dataHolder(dh) {}

        // TODO make this abstract after all operations are implemented
        virtual int run(int tid) const {
            sleep(1);
            return 0;
        }

        virtual ~Operation() {
        }

    public:
        // TODO or use pointer to operation type object
        const enum optype type;

        const char *name;

    protected:
        DataHolder *dataHolder;
    };

    class Operations {
    public:
        Operations(DataHolder *dh) {
            initOperationTypes();
            initOperations(dh);
            generateCdf();
        }

    public:
        int size() const {
            return ops.size();
        }

        vector<OperationType> &getOperationTypes() {
            return optypes;
        }

        const vector<Operation *> &getOperations() const {
            return ops;
        }

        const vector<double> &getOperationCdf() const {
            return cdf;
        }

    private:
        void initOperationTypes();

        void initOperations(DataHolder *dh);

        void initOperationsNoLock(DataHolder *dh);

        void initOperationsLockCoarse(DataHolder *dh);

        void initOperationsLockMedium(DataHolder *dh);

        void initOperationsLockFine(DataHolder *dh);

        void initOperationsLockCA(DataHolder *dh);

        void initOperationsLockDom(DataHolder *dh);

        void initOperationsLockMid(DataHolder *dh);

        void generateCdf();

    private:
        vector<OperationType> optypes;

        vector<Operation *> ops;

        vector<double> cdf;
    };
}

#endif
