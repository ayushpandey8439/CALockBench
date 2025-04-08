#ifndef SB7_LF_STRUCTURAL_MODIFICATION_H_
#define SB7_LF_STRUCTURAL_MODIFICATION_H_

#include "../operations.h"

namespace sb7 {

    class LFStructuralModification1 : public Operation {
    public:
        LFStructuralModification1(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM1", dh) {
        }

        virtual int run() const;
    };

    class LFStructuralModification2 : public Operation {
    public:
        LFStructuralModification2(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM2", dh) {
        }

        virtual int run() const;
    };

    class LFStructuralModification3 : public Operation {
    public:
        LFStructuralModification3(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM3", dh) {
        }

        virtual int run() const;
    };

    class LFStructuralModification4 : public Operation {
    public:
        LFStructuralModification4(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM4", dh) {
        }

        virtual int run() const;
    };

    class LFStructuralModification5 : public Operation {
    public:
        LFStructuralModification5(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM5", dh) {
        }

        virtual int run() const;
    };

    class LFStructuralModification6 : public Operation {
    public:
        LFStructuralModification6(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM6", dh) {
        }

        virtual int run() const;
    };

    class LFStructuralModification7 : public Operation {
    public:
        LFStructuralModification7(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM7", dh) {
        }

        virtual int run() const;
    };

    class LFStructuralModification8 : public Operation {
    public:
        LFStructuralModification8(DataHolder *dh)
                : Operation(STRUCTURAL_MODIFICATION, "SM8", dh) {
        }

        virtual int run() const;
    };

}

#endif // SB7_LF_STRUCTURAL_MODIFICATION_H_
