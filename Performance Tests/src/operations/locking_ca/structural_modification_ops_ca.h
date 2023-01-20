//
// Created by Ayush Pandey on 15/11/2022.
//

#ifndef STMBENCH_STRUCTURAL_MODIFICATION_OPS_CA_H
#define STMBENCH_STRUCTURAL_MODIFICATION_OPS_CA_H


#include "../operations.h"

namespace sb7 {

    class CAStructuralModification2 : public Operation {
    public:
        explicit CAStructuralModification2(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM2", dh) {
        }

        int run(int tid) const override;
    };

    class CAStructuralModification3 : public Operation {
    public:
        explicit CAStructuralModification3(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM3", dh) {
        }

        int run(int tid) const override;
    };
}

#endif //STMBENCH_STRUCTURAL_MODIFICATION_OPS_CA_H
