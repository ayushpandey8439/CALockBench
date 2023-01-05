#include <pthread.h>
#include <cmath>
#include <iostream>
#include <set>

#include "thread.h"
#include "thread_fun.h"

#include "../data_holder.h"
#include "../sb7_exception.h"

// TODO move it to some header
#define MIN(a, b) ((a) < (b)) ? (a) : (b)

void *sb7::init_data_holder(void *data) {
    init_thread_init();

    auto *dataHolder = (DataHolder *) data;
    dataHolder->init();

    thread_clean();

    // just return something
    return nullptr;
}

void *sb7::worker_thread(void *data) {
    thread_init();

    auto *wtdata = (WorkerThreadData *) data;

    while (!wtdata->stopped) {
        int opind = wtdata->getOperationRndInd();
        const Operation *op = wtdata->operations->getOperations()[opind];

        try {
            // get start time
            long start_time = get_time_ms();
            op->run(wtdata->threadId);
            long end_time = get_time_ms();

            wtdata->successful_ops[opind]++;
            int ttc = (int) (end_time - start_time);

            if (ttc <= wtdata->max_low_ttc) {
                wtdata->operations_ttc[opind][ttc]++;
            } else {
                double logHighTtc = (::log(ttc) - wtdata->max_low_ttc_log) /
                                    wtdata->high_ttc_log_base;
                int intLogHighTtc =
                        MIN((int) logHighTtc, wtdata->high_ttc_entries - 1);
                wtdata->operations_high_ttc_log[opind][intLogHighTtc]++;
            }

        } catch (Sb7Exception) {
            wtdata->failed_ops[opind]++;
        }
    }

    thread_clean();

    // just return something
    return nullptr;
}

int sb7::WorkerThreadData::getOperationRndInd() const {
    double oprnd = get_random()->nextDouble();
    const std::vector<double> &opRat = operations->getOperationCdf();
    int opind = 0;
    double maxPossible = opRat.at(opRat.size()-1);
    oprnd = 1-oprnd;
    oprnd *= maxPossible;
    while (opRat[opind] < oprnd && opind < opRat.size()-1) {
        opind++;
    }

    return opind;
}
