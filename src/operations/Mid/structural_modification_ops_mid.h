#ifndef SB7_Mid_STRUCTURAL_MODIFICATION_H_
#define SB7_Mid_STRUCTURAL_MODIFICATION_H_

#include "../operations.h"

namespace sb7 {

    class MidStructuralModification1 : public Operation {
    public:
        MidStructuralModification1(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM1", dh) {
        }

        virtual int run(int tid) const;
    };

    class MidStructuralModification2 : public Operation {
    public:
        MidStructuralModification2(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM2", dh) {
        }

        virtual int run(int tid) const;
    };

    class MidStructuralModification3 : public Operation {
    public:
        MidStructuralModification3(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM3", dh) {
        }

        virtual int run(int tid) const;
    };

    class MidStructuralModification4 : public Operation {
    public:
        MidStructuralModification4(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM4", dh) {
        }

        virtual int run(int tid) const;
    };

    class MidStructuralModification5 : public Operation {
    public:
        MidStructuralModification5(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM5", dh) {
        }

        virtual int run(int tid) const;
    };

    class MidStructuralModification6 : public Operation {
    public:
        MidStructuralModification6(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM6", dh) {
        }

        virtual int run(int tid) const;
    };

    class MidStructuralModification7 : public Operation {
    public:
        MidStructuralModification7(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM7", dh) {
        }

        virtual int run(int tid) const;
    };

    class MidStructuralModification8 : public Operation {
    public:
        MidStructuralModification8(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM8", dh) {
        }

        virtual int run(int tid) const;
    };

}


#endif // SB7_Mid_STRUCTURAL_MODIFICATION_H_
