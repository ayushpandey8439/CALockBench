#ifndef SB7_Dom_QUERY_OPS_
#define SB7_Dom_QUERY_OPS_

#include "../operations.h"

namespace sb7 {

	class DomQuery1 : public Operation {
		protected:
			DomQuery1(optype t, const char *n, DataHolder *dh)
				: Operation(t, n, dh) {
			}

		public:
			DomQuery1(DataHolder *dh) : Operation(OPERATION_RO, "Q1", dh) {
			}

			virtual int run(int tid) const;

		protected:
			int innerRun(int tid) const;
			virtual void performOperationOnAtomicPart(AtomicPart *apart) const;
	};

	class DomQuery2 : public Operation {
		public:
			DomQuery2(DataHolder *dh, optype t = OPERATION_RO,
				const char *n = "Q2", int percent = 1);

			virtual int run(int tid) const;

		protected:
			int innerRun(int tid) const;
			virtual void performOperationOnAtomicPart(AtomicPart *apart) const;

		private:
	    	int maxAtomicDate;
			int minAtomicDate; 
	};

	class DomQuery3 : public DomQuery2 {
		public:
			DomQuery3(DataHolder *dh) : DomQuery2(dh, OPERATION_RO, "Q3", 10) {
			}
	};

	class DomQuery4 : public Operation {
		public:
			DomQuery4(DataHolder *dh) : Operation(SHORT_TRAVERSAL_RO, "Q4", dh) {
			}

			virtual int run(int tid) const;
	};

	class DomQuery5 : public Operation {
		protected:
			DomQuery5(optype t, const char *n, DataHolder *dh)
				: Operation(t, n, dh) {
			}

		public:
			DomQuery5(DataHolder *dh) : Operation(SHORT_TRAVERSAL_RO, "Q5", dh) {
			}

			virtual int run(int tid) const;

		protected:
			int checkBaseAssembly(BaseAssembly *bassm) const;
	};

	class DomQuery6 : public DomQuery5 {
		public:
			DomQuery6(DataHolder *dh) : DomQuery5(TRAVERSAL_RO, "Q6", dh) {
			}

			virtual int run(int tid) const;

		protected:
			int checkAssembly(Assembly *assembly) const;
			int checkComplexAssembly(ComplexAssembly *assembly) const;
	};

	class DomQuery7 : public Operation {
		public:
			DomQuery7(DataHolder *dh) : Operation(TRAVERSAL_RO, "Q7", dh) {
			}

			virtual int run(int tid) const;
	};
}

#endif // SB7_Dom_QUERY_OPS_
