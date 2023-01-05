//
// Created by Ayush Pandey on 15/11/2022.
//

#ifndef STMBENCH_RANDOM_H
#define STMBENCH_RANDOM_H
#include "random"

namespace sb7 {
    class Random {
    public:
        Random();

        int nextInt();

        int nextInt(int n);

        double nextDouble();

    protected:
        std::mt19937_64 generator;
    };
}

#endif //STMBENCH_RANDOM_H
