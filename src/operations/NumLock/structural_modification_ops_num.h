#ifndef SB7_Num_STRUCTURAL_MODIFICATION_H_
#define SB7_Num_STRUCTURAL_MODIFICATION_H_

#include "../operations.h"

namespace sb7 {

    class NumStructuralModification1 : public Operation {
    public:
        NumStructuralModification1(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM1", dh) {
        }

        virtual int run(int tid) const;
    };

    class NumStructuralModification2 : public Operation {
    public:
        NumStructuralModification2(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM2", dh) {
        }

        virtual int run(int tid) const;
    };

    class NumStructuralModification3 : public Operation {
    public:
        NumStructuralModification3(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM3", dh) {
        }

        virtual int run(int tid) const;
    };

    class NumStructuralModification4 : public Operation {
    public:
        NumStructuralModification4(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM4", dh) {
        }

        virtual int run(int tid) const;
    };

    class NumStructuralModification5 : public Operation {
    public:
        NumStructuralModification5(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM5", dh) {
        }

        virtual int run(int tid) const;
    };

    class NumStructuralModification6 : public Operation {
    public:
        NumStructuralModification6(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM6", dh) {
        }

        virtual int run(int tid) const;
    };

    class NumStructuralModification7 : public Operation {
    public:
        NumStructuralModification7(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM7", dh) {
        }

        virtual int run(int tid) const;
    };

    class NumStructuralModification8 : public Operation {
    public:
        NumStructuralModification8(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM8", dh) {
        }

        virtual int run(int tid) const;
    };

}


#endif // SB7_Num_STRUCTURAL_MODIFICATION_H_
