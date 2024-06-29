//
// Created by Ayush Pandey on 15/11/2022.
//

#ifndef STMBENCH_RANDOM_H
#define STMBENCH_RANDOM_H
#include <random>

namespace sb7 {
    static std::minstd_rand0 generator(1227992885);

    class Random {

    public:

        static int nextInt() {
            std::uniform_int_distribution<int> distribution(0,std::numeric_limits<int>::max());
            return distribution(generator);
        }

        static int nextInt(int n) {
            std::uniform_int_distribution<int> distribution(0,n-1);
            return distribution(generator);
            //        return randomGen.IRandom(0, n - 1);
        }

        static double nextDouble()
        {
            std::uniform_real_distribution<double> distribution(0,1);
            return distribution(generator);
        }
    };
}

#endif //STMBENCH_RANDOM_H