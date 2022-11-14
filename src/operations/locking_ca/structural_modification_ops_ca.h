//
// Created by Ayush Pandey on 15/11/2022.
//

#ifndef STMBENCH_STRUCTURAL_MODIFICATION_OPS_CA_H
#define STMBENCH_STRUCTURAL_MODIFICATION_OPS_CA_H


#include "../operations.h"

namespace sb7 {

    class CAStructuralModification1 : public Operation {
    public:
        explicit CAStructuralModification1(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM1", dh) {
        }

        int run() const override;
    };

    class CAStructuralModification2 : public Operation {
    public:
        explicit CAStructuralModification2(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM2", dh) {
        }

        int run() const override;
    };

    class CAStructuralModification3 : public Operation {
    public:
        explicit CAStructuralModification3(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM3", dh) {
        }

        int run() const override;
    };

    class CAStructuralModification4 : public Operation {
    public:
        explicit CAStructuralModification4(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM4", dh) {
        }

        int run() const override;
    };

    class CAStructuralModification5 : public Operation {
    public:
        explicit CAStructuralModification5(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM5", dh) {
        }

        int run() const override;
    };

    class CAStructuralModification6 : public Operation {
    public:
        explicit CAStructuralModification6(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM6", dh) {
        }

        int run() const override;
    };

    class CAStructuralModification7 : public Operation {
    public:
        explicit CAStructuralModification7(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM7", dh) {
        }

        int run() const override;
    };

    class CAStructuralModification8 : public Operation {
    public:
        explicit CAStructuralModification8(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM8", dh) {
        }

        int run() const override;
    };

}

#endif //STMBENCH_STRUCTURAL_MODIFICATION_OPS_CA_H
