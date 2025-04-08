#ifndef SB7_LM_STRUCTURAL_MODIFICATION_H_
#define SB7_LM_STRUCTURAL_MODIFICATION_H_

#include "../operations.h"

namespace sb7 {

    class LMStructuralModification1 : public Operation {
    public:
        LMStructuralModification1(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM1", dh) {
        }

        int run(int tid) const override;
    };

    class LMStructuralModification2 : public Operation {
    public:
        LMStructuralModification2(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM2", dh) {
        }

        int run(int tid) const override;
    };

    class LMStructuralModification3 : public Operation {
    public:
        LMStructuralModification3(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM3", dh) {
        }

        int run(int tid) const override;
    };

    class LMStructuralModification4 : public Operation {
    public:
        LMStructuralModification4(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM4", dh) {
        }

        int run(int tid) const override;
    };

    class LMStructuralModification5 : public Operation {
    public:
        LMStructuralModification5(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM5", dh) {
        }

        int run(int tid) const override;
    };

    class LMStructuralModification6 : public Operation {
    public:
        LMStructuralModification6(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM6", dh) {
        }

        int run(int tid) const override;
    };

    class LMStructuralModification7 : public Operation {
    public:
        LMStructuralModification7(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM7", dh) {
        }

        int run(int tid) const override;
    };

    class LMStructuralModification8 : public Operation {
    public:
        LMStructuralModification8(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM8", dh) {
        }

        int run(int tid) const override;
    };

}

#endif // SB7_LM_STRUCTURAL_MODIFICATION_H_
