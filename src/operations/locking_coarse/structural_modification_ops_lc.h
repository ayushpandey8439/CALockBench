#ifndef SB7_LC_STRUCTURAL_MODIFICATION_H_
#define SB7_LC_STRUCTURAL_MODIFICATION_H_

#include "../operations.h"

namespace sb7 {

    class LCStructuralModification1 : public Operation {
    public:
        LCStructuralModification1(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM1", dh) {
        }

        int run(int tid) const override;
    };

    class LCStructuralModification2 : public Operation {
    public:
        LCStructuralModification2(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM2", dh) {
        }

        int run(int tid) const override;
    };

    class LCStructuralModification3 : public Operation {
    public:
        LCStructuralModification3(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM3", dh) {
        }

        int run(int tid) const override;
    };

    class LCStructuralModification4 : public Operation {
    public:
        LCStructuralModification4(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM4", dh) {
        }

        int run(int tid) const override;
    };

    class LCStructuralModification5 : public Operation {
    public:
        LCStructuralModification5(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM5", dh) {
        }

        int run(int tid) const override;
    };

    class LCStructuralModification6 : public Operation {
    public:
        LCStructuralModification6(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM6", dh) {
        }

        int run(int tid) const override;
    };

    class LCStructuralModification7 : public Operation {
    public:
        LCStructuralModification7(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM7", dh) {
        }

        int run(int tid) const override;
    };

    class LCStructuralModification8 : public Operation {
    public:
        LCStructuralModification8(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM8", dh) {
        }

        int run(int tid) const override;
    };

}

#endif // SB7_LC_STRUCTURAL_MODIFICATION_H_
