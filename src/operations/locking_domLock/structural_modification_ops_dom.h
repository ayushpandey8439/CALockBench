#ifndef SB7_Dom_STRUCTURAL_MODIFICATION_H_
#define SB7_Dom_STRUCTURAL_MODIFICATION_H_

#include "../operations.h"

namespace sb7 {

	class DomStructuralModification1 : public Operation {
		public:
			DomStructuralModification1(DataHolder *dh)
				: Operation(STRUCTURAL_MODIFICATION, "SM1", dh) {
			}

			virtual int run(int tid) const;
	};

	class DomStructuralModification2 : public Operation {
		public:
			DomStructuralModification2(DataHolder *dh)
				: Operation(STRUCTURAL_MODIFICATION, "SM2", dh) {
			}

			virtual int run(int tid) const;
	};

	class DomStructuralModification3 : public Operation {
		public:
			DomStructuralModification3(DataHolder *dh)
				: Operation(STRUCTURAL_MODIFICATION, "SM3", dh) {
			}

			virtual int run(int tid) const;
	};

	class DomStructuralModification4 : public Operation {
		public:
			DomStructuralModification4(DataHolder *dh)
				: Operation(STRUCTURAL_MODIFICATION, "SM4", dh) {
			}

			virtual int run(int tid) const;
	};

	class DomStructuralModification5 : public Operation {
		public:
			DomStructuralModification5(DataHolder *dh)
				: Operation(STRUCTURAL_MODIFICATION, "SM5", dh) {
			}

			virtual int run(int tid) const;
	};

	class DomStructuralModification6 : public Operation {
		public:
			DomStructuralModification6(DataHolder *dh)
				: Operation(STRUCTURAL_MODIFICATION, "SM6", dh) {
			}

			virtual int run(int tid) const;
	};

	class DomStructuralModification7 : public Operation {
		public:
			DomStructuralModification7(DataHolder *dh)
				: Operation(STRUCTURAL_MODIFICATION, "SM7", dh) {
			}

			virtual int run(int tid) const;
	};

	class DomStructuralModification8 : public Operation {
		public:
			DomStructuralModification8(DataHolder *dh)
				: Operation(STRUCTURAL_MODIFICATION, "SM8", dh) {
			}

			virtual int run(int tid) const;
	};

}

#endif // SB7_Dom_STRUCTURAL_MODIFICATION_H_
