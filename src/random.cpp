#include <limits>

#include "thread/thread.h"
#include "random.h"
//The seed should allow us to get duplicable results such that the same hierarchy is created and benchmarked for all the lock types and locking strategies.
uint32 seed = 12345;
namespace sb7 {
    Random::Random() : randomGen(TRandomMersenne(seed)) {
    }

    int Random::nextInt() {
        return randomGen.IRandom(0, std::numeric_limits<int>::max());
    }

    int Random::nextInt(int n) {
        return randomGen.IRandom(0, n - 1);
    }

    double Random::nextDouble() {
        return randomGen.Random();
    }
}
