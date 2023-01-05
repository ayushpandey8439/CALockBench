#include <iostream>

#include "parameters.h"
#include "benchmark.h"
#include "lockPool.h"
#include "struct/assembly.h"
#include "shared_mutex"
#include "interval.h"
using namespace sb7;
lockPool pool;
IntervalCheck ICheck;

int main(int argc, char **argv) {
    // initialize parameters
    if (parameters.init(argc, argv, cout)) {
        parameters.print(cout);

        // create benchmark object and run it
        Benchmark benchmark;
        benchmark.init();
        benchmark.start();
        benchmark.report(cout);
    }
}
