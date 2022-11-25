//
// Created by Ayush Pandey on 15/11/2022.
//

#ifndef STMBENCH_STRUCTURAL_MODIFICATION_OPS_LC_H
#define STMBENCH_STRUCTURAL_MODIFICATION_OPS_LC_H


#include "../operations.h"

namespace sb7 {

    class LCStructuralModification1 : public Operation {
    public:
        explicit LCStructuralModification1(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM1", dh) {
        }

        int run(int tid) const override;
    };

    class LCStructuralModification2 : public Operation {
    public:
        explicit LCStructuralModification2(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM2", dh) {
        }

        int run(int tid) const override;
    };

    class LCStructuralModification3 : public Operation {
    public:
        explicit LCStructuralModification3(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM3", dh) {
        }

        int run(int tid) const override;
    };

    class LCStructuralModification4 : public Operation {
    public:
        explicit LCStructuralModification4(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM4", dh) {
        }

        int run(int tid) const override;
    };

    class LCStructuralModification5 : public Operation {
    public:
        explicit LCStructuralModification5(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM5", dh) {
        }

        int run(int tid) const override;
    };

    class LCStructuralModification6 : public Operation {
    public:
        explicit LCStructuralModification6(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM6", dh) {
        }

        int run(int tid) const override;
    };

    class LCStructuralModification7 : public Operation {
    public:
        explicit LCStructuralModification7(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM7", dh) {
        }

        int run(int tid) const override;
    };

    class LCStructuralModification8 : public Operation {
    public:
        explicit LCStructuralModification8(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM8", dh) {
        }

        int run(int tid) const override;
    };

}

#endif //STMBENCH_STRUCTURAL_MODIFICATION_OPS_LC_H
