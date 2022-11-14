//
// Created by Ayush Pandey on 15/11/2022.
//

#ifndef STMBENCH_STRUCTURAL_MODIFICATION_OPS_LM_H
#define STMBENCH_STRUCTURAL_MODIFICATION_OPS_LM_H


#include "../operations.h"

namespace sb7 {

    class LMStructuralModification1 : public Operation {
    public:
        explicit LMStructuralModification1(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM1", dh) {
        }

        int run() const override;
    };

    class LMStructuralModification2 : public Operation {
    public:
        explicit LMStructuralModification2(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM2", dh) {
        }

        int run() const override;
    };

    class LMStructuralModification3 : public Operation {
    public:
        explicit LMStructuralModification3(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM3", dh) {
        }

        int run() const override;
    };

    class LMStructuralModification4 : public Operation {
    public:
        explicit LMStructuralModification4(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM4", dh) {
        }

        int run() const override;
    };

    class LMStructuralModification5 : public Operation {
    public:
        explicit LMStructuralModification5(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM5", dh) {
        }

        int run() const override;
    };

    class LMStructuralModification6 : public Operation {
    public:
        explicit LMStructuralModification6(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM6", dh) {
        }

        int run() const override;
    };

    class LMStructuralModification7 : public Operation {
    public:
        explicit LMStructuralModification7(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM7", dh) {
        }

        int run() const override;
    };

    class LMStructuralModification8 : public Operation {
    public:
        explicit LMStructuralModification8(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM8", dh) {
        }

        int run() const override;
    };

}


#endif //STMBENCH_STRUCTURAL_MODIFICATION_OPS_LM_H
