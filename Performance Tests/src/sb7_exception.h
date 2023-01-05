//
// Created by Ayush Pandey on 15/11/2022.
//

#ifndef STMBENCH_SB7_EXCEPTION_H
#define STMBENCH_SB7_EXCEPTION_H
namespace sb7 {

    class Sb7Exception {
    public:
        Sb7Exception() = default;

        explicit Sb7Exception(const char *m) : msg(m) {
        }

    protected:
        const char *msg{};
    };

}

#endif //STMBENCH_SB7_EXCEPTION_H
