#ifndef SB7_LF_QUERY_OPS_
#define SB7_LF_QUERY_OPS_

#include "../operations.h"

namespace sb7 {

	class LFQuery1 : public Operation {
		protected:
			LFQuery1(optype t, const char *n, DataHolder *dh)
				: Operation(t, n, dh) {
			}

		public:
			LFQuery1(DataHolder *dh) : Operation(OPERATION_RO, "Q1", dh) {
			}

			virtual int run() const;

		protected:
			virtual void performOperationOnAtomicPart(AtomicPart *apart) const;
	};

	class LFQuery2 : public Operation {
		public:
			LFQuery2(DataHolder *dh, optype t = OPERATION_RO,
				const char *n = "Q2", int percent = 1);

			virtual int run() const;

		protected:
			virtual void performOperationOnAtomicPart(AtomicPart *apart) const;

		private:
	    	int maxAtomicDate;
			int minAtomicDate; 
	};

	class LFQuery3 : public LFQuery2 {
		public:
			LFQuery3(DataHolder *dh) : LFQuery2(dh, OPERATION_RO, "Q3", 10) {
			}
	};

	class LFQuery4 : public Operation {
		public:
			LFQuery4(DataHolder *dh) : Operation(SHORT_TRAVERSAL_RO, "Q4", dh) {
			}

			virtual int run() const;
	};

	class LFQuery5 : public Operation {
		protected:
			LFQuery5(optype t, const char *n, DataHolder *dh)
				: Operation(t, n, dh) {
			}

		public:
			LFQuery5(DataHolder *dh) : Operation(SHORT_TRAVERSAL_RO, "Q5", dh) {
			}

			virtual int run() const;

		protected:
			int checkBaseAssembly(BaseAssembly *bassm) const;
	};

	class LFQuery6 : public LFQuery5 {
		public:
			LFQuery6(DataHolder *dh) : LFQuery5(TRAVERSAL_RO, "Q6", dh) {
			}

			virtual int run() const;

		protected:
			int checkAssembly(Assembly *assembly) const;
			int checkComplexAssembly(ComplexAssembly *assembly) const;
	};

	class LFQuery7 : public Operation {
		public:
			LFQuery7(DataHolder *dh) : Operation(TRAVERSAL_RO, "Q7", dh) {
			}

			virtual int run() const;
	};
}

#endif // SB7_LF_QUERY_OPS_
