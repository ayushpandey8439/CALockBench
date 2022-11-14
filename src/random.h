//
// Created by Ayush Pandey on 15/11/2022.
//

#ifndef STMBENCH_RANDOM_H
#define STMBENCH_RANDOM_H


#include "randomc/randomc.h"

namespace sb7 {
    class Random {
    public:
        Random();

        int nextInt();

        int nextInt(int n);

        double nextDouble();

    private:
        TRandomMersenne randomGen;
    };
}

#endif //STMBENCH_RANDOM_H
