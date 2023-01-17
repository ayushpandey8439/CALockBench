#include <limits>

#include "thread/thread.h"
#include "random.h"
//The seed should allow us to get duplicable results such that the same hierarchy is created and benchmarked for all the lock types and locking strategies.
unsigned seed = 12345;
namespace sb7 {
    Random::Random() : generator(seed){
    }

    int Random::nextInt() {
        std::uniform_int_distribution<int> distribution(0,std::numeric_limits<int>::max());
        return distribution(generator);
    }

    int Random::nextInt(int n) {
        std::uniform_int_distribution<int> distribution(0,n-1);
        return distribution(generator);
//        return randomGen.IRandom(0, n - 1);
    }

    double Random::nextDouble() {
        std::uniform_real_distribution<double> distribution(0.0,1.0);
        return distribution(generator);
    }
}
