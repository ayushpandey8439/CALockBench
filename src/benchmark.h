//
// Created by Ayush Pandey on 15/11/2022.
//

#ifndef STMBENCH_BENCHMARK_H
#define STMBENCH_BENCHMARK_H


#include <pthread.h>
#include <iostream>

#include "data_holder.h"
#include "thread/thread_fun.h"
#include "operations/operations.h"

#define MAX_THREADS 256

namespace sb7 {
    /**
     * Class that encapsulates all elements of a benchmark.
     */
    class Benchmark {
    public:
        Benchmark();

        ~Benchmark();

        // this includes initialization of data structure used in the
        // benchmark, not other data
        void init();

        void start();

        void dbg();

        void report(ostream &out = std::cout);

    private:
        static int *create_array(int size) ;

        int **create_matrix(int rows, int cols) const;

        static void free_matrix(int **matrix, int rows) ;

        // short for getting number of operations
        int getOperationNum() const {
            return operations.size();
        }

        void reportTtcHistograms(ostream &out) const;

        // reporting stats
        void reportStats(ostream &out);

        struct opstats {
            int succ;
            int fail;
            int maxttc;
        };

        opstats calcOpstats(int opind, int thnum);

        int calcMaxTtc(int opind, int thind) const;

        static int logTtcIndToTtc(int logTtcInd) ;

        static void updateOperationTypeStats(OperationType &optype,
                                      const opstats &os);

        void printSection(ostream &out, const char *text) const;

    private:
        DataHolder dataHolder;

        Operations operations;

        struct {
            pthread_t tid;
            WorkerThreadData wtdata;
        } threads[MAX_THREADS]{};

        long elapsedTime;
    };
}


#endif //STMBENCH_BENCHMARK_H
