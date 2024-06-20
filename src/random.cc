#include <limits>

#include "thread/thread.h"
#include "random.h"

namespace sb7 {
    Random::Random() : randomGen(TRandomMersenne(get_time_us() % 1000)) {
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
