#ifndef SB7_Flexi_STRUCTURAL_MODIFICATION_H_
#define SB7_Flexi_STRUCTURAL_MODIFICATION_H_

#include "../operations.h"

namespace sb7 {

    class FlexiStructuralModification1 : public Operation {
    public:
        FlexiStructuralModification1(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM1", dh) {
        }

        virtual int run(int tid) const;
    };

    class FlexiStructuralModification2 : public Operation {
    public:
        FlexiStructuralModification2(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM2", dh) {
        }

        virtual int run(int tid) const;
    };

    class FlexiStructuralModification3 : public Operation {
    public:
        FlexiStructuralModification3(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM3", dh) {
        }

        virtual int run(int tid) const;
    };

    class FlexiStructuralModification4 : public Operation {
    public:
        FlexiStructuralModification4(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM4", dh) {
        }

        virtual int run(int tid) const;
    };

    class FlexiStructuralModification5 : public Operation {
    public:
        FlexiStructuralModification5(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM5", dh) {
        }

        virtual int run(int tid) const;
    };

    class FlexiStructuralModification6 : public Operation {
    public:
        FlexiStructuralModification6(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM6", dh) {
        }

        virtual int run(int tid) const;
    };

    class FlexiStructuralModification7 : public Operation {
    public:
        FlexiStructuralModification7(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM7", dh) {
        }

        virtual int run(int tid) const;
    };

    class FlexiStructuralModification8 : public Operation {
    public:
        FlexiStructuralModification8(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM8", dh) {
        }

        virtual int run(int tid) const;
    };

}

#endif // SB7_Flexi_STRUCTURAL_MODIFICATION_H_
