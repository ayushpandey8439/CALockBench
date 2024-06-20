#ifndef SB7_QUERY_OPS_
#define SB7_QUERY_OPS_

#include "../operations.h"

namespace sb7 {

	class Query1 : public Operation {
		protected:
			Query1(optype t, const char *n, DataHolder *dh)
				: Operation(t, n, dh) {
			}

		public:
			Query1(DataHolder *dh) : Operation(OPERATION_RO, "Q1", dh) {
			}

			virtual int run() const;

		protected:
			virtual void performOperationOnAtomicPart(AtomicPart *apart) const;
	};

	class Query2 : public Operation {
		public:
			Query2(DataHolder *dh, optype t = OPERATION_RO,
				const char *n = "Q2", int percent = 1);

			virtual int run() const;

		protected:
			virtual void performOperationOnAtomicPart(AtomicPart *apart) const;

		private:
	    	int maxAtomicDate;
			int minAtomicDate; 
	};

	class Query3 : public Query2 {
		public:
			Query3(DataHolder *dh) : Query2(dh, OPERATION_RO, "Q3", 10) {
			}
	};

	class Query4 : public Operation {
		public:
			Query4(DataHolder *dh) : Operation(SHORT_TRAVERSAL_RO, "Q4", dh) {
			}

			virtual int run() const;
	};

	class Query5 : public Operation {
		protected:
			Query5(optype t, const char *n, DataHolder *dh)
				: Operation(t, n, dh) {
			}

		public:
			Query5(DataHolder *dh) : Operation(SHORT_TRAVERSAL_RO, "Q5", dh) {
			}

			virtual int run() const;

		protected:
			int checkBaseAssembly(BaseAssembly *bassm) const;
	};

	class Query6 : public Query5 {
		public:
			Query6(DataHolder *dh) : Query5(TRAVERSAL_RO, "Q6", dh) {
			}

			virtual int run() const;

		protected:
			int checkAssembly(Assembly *assembly) const;
			int checkComplexAssembly(ComplexAssembly *assembly) const;
	};

	class Query7 : public Operation {
		public:
			Query7(DataHolder *dh) : Operation(TRAVERSAL_RO, "Q7", dh) {
			}

			virtual int run() const;
	};
}

#endif // SB7_QUERY_OPS_
