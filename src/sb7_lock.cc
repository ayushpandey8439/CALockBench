#include <iostream>

#include "parameters.h"
#include "benchmark.h"

#include "operations/CALock/CAPool.h"
#include "operations/DomLock/DomPool.h"
#include "operations/Flexigran/FlexiPool.h"
#include "operations/IntentionLock/Intention_lock_srv.h"
#include "operations/Mid/MidPool.h"
#include "operations/NumLock/NumPool.h"

using namespace sb7;
using namespace std;
CAPool caPool;
DomPool domPool;
MidPool midPool;
NumPool numPool;
FlexiPool flexiPool;
Intention_lock_srv ILSrv;

int fgPercent; // TODO: Initialise in parameters


int numBuckets;
int numIterations;
int numNodesLocked;
int totalLockRejections;
int correctedFScountByTraversal;
int correctedFScountByMID;
int totalNumOps;
int totalLockAttempts;
int correctedByDL;
int numTraversals;
long totalNumEdgesTraversed;

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
