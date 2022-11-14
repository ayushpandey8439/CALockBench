#include <iostream>

#include "parameters.h"
#include "benchmark.h"

#include "struct/assembly.h"

using namespace sb7;

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
