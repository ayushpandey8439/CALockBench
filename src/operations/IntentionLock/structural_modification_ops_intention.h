#ifndef SB7_Intention_STRUCTURAL_MODIFICATION_H_
#define SB7_Intention_STRUCTURAL_MODIFICATION_H_

#include "../operations.h"

namespace sb7 {

    class IntentionStructuralModification1 : public Operation {
    public:
        IntentionStructuralModification1(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM1", dh) {
        }

        int run(int tid) const override;
    };

    class IntentionStructuralModification2 : public Operation {
    public:
        IntentionStructuralModification2(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM2", dh) {
        }

        int run(int tid) const override;
    };

    class IntentionStructuralModification3 : public Operation {
    public:
        IntentionStructuralModification3(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM3", dh) {
        }

        int run(int tid) const override;
    };

    class IntentionStructuralModification4 : public Operation {
    public:
        IntentionStructuralModification4(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM4", dh) {
        }

        int run(int tid) const override;
    };

    class IntentionStructuralModification5 : public Operation {
    public:
        IntentionStructuralModification5(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM5", dh) {
        }

        int run(int tid) const override;
    };

    class IntentionStructuralModification6 : public Operation {
    public:
        IntentionStructuralModification6(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM6", dh) {
        }

        int run(int tid) const override;
    };

    class IntentionStructuralModification7 : public Operation {
    public:
        IntentionStructuralModification7(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM7", dh) {
        }

        int run(int tid) const override;
    };

    class IntentionStructuralModification8 : public Operation {
    public:
        IntentionStructuralModification8(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM8", dh) {
        }

        int run(int tid) const override;
    };

}

#endif // SB7_Intention_STRUCTURAL_MODIFICATION_H_
