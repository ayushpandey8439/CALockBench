#ifndef SB7_LM_STRUCTURAL_MODIFICATION_H_
#define SB7_LM_STRUCTURAL_MODIFICATION_H_

#include "../operations.h"

namespace sb7 {

    class LMStructuralModification1 : public Operation {
    public:
        LMStructuralModification1(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM1", dh) {
        }

        virtual int run() const;
    };

    class LMStructuralModification2 : public Operation {
    public:
        LMStructuralModification2(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM2", dh) {
        }

        virtual int run() const;
    };

    class LMStructuralModification3 : public Operation {
    public:
        LMStructuralModification3(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM3", dh) {
        }

        virtual int run() const;
    };

    class LMStructuralModification4 : public Operation {
    public:
        LMStructuralModification4(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM4", dh) {
        }

        virtual int run() const;
    };

    class LMStructuralModification5 : public Operation {
    public:
        LMStructuralModification5(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM5", dh) {
        }

        virtual int run() const;
    };

    class LMStructuralModification6 : public Operation {
    public:
        LMStructuralModification6(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM6", dh) {
        }

        virtual int run() const;
    };

    class LMStructuralModification7 : public Operation {
    public:
        LMStructuralModification7(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM7", dh) {
        }

        virtual int run() const;
    };

    class LMStructuralModification8 : public Operation {
    public:
        LMStructuralModification8(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM8", dh) {
        }

        virtual int run() const;
    };

}

#endif // SB7_LM_STRUCTURAL_MODIFICATION_H_
