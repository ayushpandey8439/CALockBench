#include <iostream>

#include "parameters.h"
#include "benchmark.h"

#include "operations/CALock/CAPool.h"
#include "operations/DomLock/DomPool.h"

using namespace sb7;
using namespace std;
CAPool pool;
DomPool ICheck;
//coarsePool cPool;
//mediumPool mPool;
int main(int argc, char **argv) {
    // initialize parameters
    if(parameters.init(argc, argv, cout)) {
        parameters.print(cout);

        // create benchmark object and run it
        Benchmark benchmark;
        benchmark.init();
        benchmark.start();
        benchmark.report(cout);
    }
}
