#ifndef SB7_LC_QUERY_OPS_
#define SB7_LC_QUERY_OPS_

#include "../operations.h"

namespace sb7 {

	class LCQuery1 : public Operation {
		protected:
			LCQuery1(optype t, const char *n, DataHolder *dh)
				: Operation(t, n, dh) {
			}

		public:
			LCQuery1(DataHolder *dh) : Operation(OPERATION_RO, "Q1", dh) {
			}

			virtual int run() const;

		protected:
			int innerRun() const;
			virtual void performOperationOnAtomicPart(AtomicPart *apart) const;
	};

	class LCQuery2 : public Operation {
		public:
			LCQuery2(DataHolder *dh, optype t = OPERATION_RO,
				const char *n = "Q2", int percent = 1);

			virtual int run() const;

		protected:
			int innerRun() const;
			virtual void performOperationOnAtomicPart(AtomicPart *apart) const;

		private:
	    	int maxAtomicDate;
			int minAtomicDate; 
	};

	class LCQuery3 : public LCQuery2 {
		public:
			LCQuery3(DataHolder *dh) : LCQuery2(dh, OPERATION_RO, "Q3", 10) {
			}
	};

	class LCQuery4 : public Operation {
		public:
			LCQuery4(DataHolder *dh) : Operation(SHORT_TRAVERSAL_RO, "Q4", dh) {
			}

			virtual int run() const;
	};

	class LCQuery5 : public Operation {
		protected:
			LCQuery5(optype t, const char *n, DataHolder *dh)
				: Operation(t, n, dh) {
			}

		public:
			LCQuery5(DataHolder *dh) : Operation(SHORT_TRAVERSAL_RO, "Q5", dh) {
			}

			virtual int run() const;

		protected:
			int checkBaseAssembly(BaseAssembly *bassm) const;
	};

	class LCQuery6 : public LCQuery5 {
		public:
			LCQuery6(DataHolder *dh) : LCQuery5(TRAVERSAL_RO, "Q6", dh) {
			}

			virtual int run() const;

		protected:
			int checkAssembly(Assembly *assembly) const;
			int checkComplexAssembly(ComplexAssembly *assembly) const;
	};

	class LCQuery7 : public Operation {
		public:
			LCQuery7(DataHolder *dh) : Operation(TRAVERSAL_RO, "Q7", dh) {
			}

			virtual int run() const;
	};
}

#endif // SB7_LC_QUERY_OPS_
