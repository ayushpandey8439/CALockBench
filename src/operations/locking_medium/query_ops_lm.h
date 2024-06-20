#ifndef SB7_LM_QUERY_OPS_
#define SB7_LM_QUERY_OPS_

#include "../operations.h"

namespace sb7 {

	class LMQuery1 : public Operation {
		protected:
			LMQuery1(optype t, const char *n, DataHolder *dh)
				: Operation(t, n, dh) {
			}

		public:
			LMQuery1(DataHolder *dh) : Operation(OPERATION_RO, "Q1", dh) {
			}

			virtual int run() const;

		protected:
			int innerRun() const;
			virtual void performOperationOnAtomicPart(AtomicPart *apart) const;
	};

	class LMQuery2 : public Operation {
		public:
			LMQuery2(DataHolder *dh, optype t = OPERATION_RO,
				const char *n = "Q2", int percent = 1);

			virtual int run() const;

		protected:
			int innerRun() const;
			virtual void performOperationOnAtomicPart(AtomicPart *apart) const;

		private:
	    	int maxAtomicDate;
			int minAtomicDate; 
	};

	class LMQuery3 : public LMQuery2 {
		public:
			LMQuery3(DataHolder *dh) : LMQuery2(dh, OPERATION_RO, "Q3", 10) {
			}
	};

	class LMQuery4 : public Operation {
		public:
			LMQuery4(DataHolder *dh) : Operation(SHORT_TRAVERSAL_RO, "Q4", dh) {
			}

			virtual int run() const;
	};

	class LMQuery5 : public Operation {
		protected:
			LMQuery5(optype t, const char *n, DataHolder *dh)
				: Operation(t, n, dh) {
			}

		public:
			LMQuery5(DataHolder *dh) : Operation(SHORT_TRAVERSAL_RO, "Q5", dh) {
			}

			virtual int run() const;

		protected:
			int checkBaseAssembly(BaseAssembly *bassm) const;
	};

	class LMQuery6 : public LMQuery5 {
		public:
			LMQuery6(DataHolder *dh) : LMQuery5(TRAVERSAL_RO, "Q6", dh) {
			}

			virtual int run() const;

		protected:
			int checkAssembly(Assembly *assembly) const;
			int checkComplexAssembly(ComplexAssembly *assembly) const;
	};

	class LMQuery7 : public Operation {
		public:
			LMQuery7(DataHolder *dh) : Operation(TRAVERSAL_RO, "Q7", dh) {
			}

			virtual int run() const;
	};
}

#endif // SB7_LM_QUERY_OPS_
