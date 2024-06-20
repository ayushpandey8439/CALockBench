#ifndef SB7_LF_TRAVERSAL_OPS_
#define SB7_LF_TRAVERSAL_OPS_

#include "../operations.h"
#include "../../containers.h"
#include "../../struct/assembly.h"

namespace sb7 {

	class LFTraversal1 : public Operation {
		protected:
			LFTraversal1(optype t, const char *n, DataHolder *dh)
				: Operation(t, n, dh) {
			}

		public:
			LFTraversal1(DataHolder *dh) : Operation(TRAVERSAL_RO, "T1", dh) {
			}

			virtual int run() const;

		protected:
			int traverse(ComplexAssembly *complexAssembly) const;
			int traverse(BaseAssembly *baseAssembly) const;
			virtual int traverse(CompositePart *component) const;
			virtual int traverse(AtomicPart *part,
				Set<AtomicPart *> &setOfVisitedParts) const;
			virtual int performOperationOnAtomicPart(AtomicPart *apart,
				Set<AtomicPart *> &setOfVisitedPartIds) const;
	};

	class LFTraversal2a : public LFTraversal1 {
		public:
			LFTraversal2a(DataHolder *dh) : LFTraversal1(TRAVERSAL, "T2a", dh) {
			}

		protected:
			virtual int performOperationOnAtomicPart(AtomicPart *apart,
				Set<AtomicPart *> &setOfVisitedPartIds) const;			
	};

	class LFTraversal2b : public LFTraversal1 {
		public:
			LFTraversal2b(DataHolder *dh) : LFTraversal1(TRAVERSAL, "T2b", dh) {
			}

		protected:
			virtual int performOperationOnAtomicPart(AtomicPart *apart,
				Set<AtomicPart *> &setOfVisitedPartIds) const;			
	};

	class LFTraversal2c : public LFTraversal1 {
		public:
			LFTraversal2c(DataHolder *dh) : LFTraversal1(TRAVERSAL, "T2c", dh) {
			}

		protected:
			virtual int performOperationOnAtomicPart(AtomicPart *apart,
				Set<AtomicPart *> &setOfVisitedPartIds) const;
	};

	class LFTraversal3a : public LFTraversal1 {
		protected:
			LFTraversal3a(optype t, const char *n, DataHolder *dh)
				: LFTraversal1(t, n, dh) {
			}

		public:
			LFTraversal3a(DataHolder *dh) : LFTraversal1(TRAVERSAL, "T3a", dh) {
			}

		protected:
			virtual int performOperationOnAtomicPart(AtomicPart *apart,
				Set<AtomicPart *> &setOfVisitedPartIds) const;

			void updateBuildDate(AtomicPart *apart) const;
	};

	class LFTraversal3b : public LFTraversal3a {
		public:
			LFTraversal3b(DataHolder *dh) : LFTraversal3a(TRAVERSAL, "T3b", dh) {
			}

		protected:
			virtual int performOperationOnAtomicPart(AtomicPart *apart,
				Set<AtomicPart *> &setOfVisitedPartIds) const;
	};

	class LFTraversal3c : public LFTraversal3a {
		public:
			LFTraversal3c(DataHolder *dh) : LFTraversal3a(TRAVERSAL, "T3c", dh) {
			}

		protected:
			virtual int performOperationOnAtomicPart(AtomicPart *apart,
				Set<AtomicPart *> &setOfVisitedPartIds) const;
	};

	class LFTraversal4 : public LFTraversal1 {
		protected:
			LFTraversal4(optype t, const char *n, DataHolder *dh)
				: LFTraversal1(t, n, dh) {
			}

		public:
			LFTraversal4(DataHolder *dh) : LFTraversal1(TRAVERSAL_RO, "T4", dh) {
			}

		protected:
			virtual int traverse(CompositePart *component) const;
			virtual int traverse(Document *doc) const;
			virtual int traverse(AtomicPart *part,
				Set<AtomicPart *> &setOfVisitedParts) const;
			virtual int performOperationOnAtomicPart(AtomicPart *apart,
				Set<AtomicPart *> &setOfVisitedPartIds) const;
	};

	class LFTraversal5 : public LFTraversal4 {
		public:
			LFTraversal5(DataHolder *dh) : LFTraversal4(TRAVERSAL, "T5", dh) {
			}

		protected:
			virtual int traverse(Document *doc) const;
	};

	class LFTraversal6 : public LFTraversal1 {
		public:
			LFTraversal6(DataHolder *dh) : LFTraversal1(TRAVERSAL_RO, "T6", dh) {
			}

		protected:
			// I made this shorter than in original bench
			virtual int traverse(CompositePart *component) const;
	};

	// following traversal is actually short traversal, but is here because
	// of it's slightly misleading name
	class LFTraversal7 : public Operation {
		protected:
			LFTraversal7(optype t, const char *n, DataHolder *dh)
				: Operation(t, n, dh) {
			}

		public:
			LFTraversal7(DataHolder *dh)
				: Operation(SHORT_TRAVERSAL_RO, "T7", dh) {
			}

			virtual int run() const;

		protected:
			int traverse(CompositePart *cpart) const;
			int traverse(Assembly *assembly,
				Set<Assembly *> &visitedAssemblies) const;
			virtual void performOperationOnAssembly(Assembly *assembly) const;
	};

	// following two traversals are actually ro operations, but are here
	// because of their slightly misleading names

	class LFTraversal8 : public Operation {
		protected:
			LFTraversal8(optype t, const char *n, DataHolder *dh)
				: Operation(t, n, dh) {
			}

		public:
			LFTraversal8(DataHolder *dh)
				: Operation(OPERATION_RO, "T8", dh) {
			}

			virtual int run() const;

		protected:
			virtual int traverse(Manual *manual) const;
	};

	class LFTraversal9 : public LFTraversal8 {
		public:
			LFTraversal9(DataHolder *dh)
				: LFTraversal8(OPERATION_RO, "T9", dh) {
			}

		protected:
			virtual int traverse(Manual *manual) const;
	};

}

#endif // SB7_LF_TRAVERSAL_OPS_
