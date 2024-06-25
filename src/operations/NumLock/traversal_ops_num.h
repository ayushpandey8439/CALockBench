#ifndef SB7_Num_TRAVERSAL_OPS_
#define SB7_Num_TRAVERSAL_OPS_

#include "../operations.h"
#include "../../containers.h"
#include "../../struct/assembly.h"

namespace sb7 {
    class NumTraversal1 : public Operation {
        protected:
            NumTraversal1(optype t, const char *n, DataHolder *dh)
                : Operation(t, n, dh) {
            }

        public:
            NumTraversal1(DataHolder *dh) : Operation(TRAVERSAL_RO, "T1", dh) {
            }

            virtual int run(int tid) const;

        protected:
            int traverse(ComplexAssembly *complexAssembly) const;
            int traverse(BaseAssembly *baseAssembly) const;
            virtual int traverse(CompositePart *component) const;
            virtual int traverse(AtomicPart *part,
                Set<AtomicPart *> &setOfVisitedParts) const;
            virtual int performOperationOnAtomicPart(AtomicPart *apart,
                Set<AtomicPart *> &setOfVisitedPartIds) const;
    };

    class NumTraversal2a : public NumTraversal1 {
        public:
            NumTraversal2a(DataHolder *dh) : NumTraversal1(TRAVERSAL, "T2a", dh) {
            }

            virtual int run(int tid) const;

        protected:
            virtual int performOperationOnAtomicPart(AtomicPart *apart,
                Set<AtomicPart *> &setOfVisitedPartIds) const;
    };

    class NumTraversal2b : public NumTraversal1 {
        public:
            NumTraversal2b(DataHolder *dh) : NumTraversal1(TRAVERSAL, "T2b", dh) {
            }

            virtual int run(int tid) const;

        protected:
            virtual int performOperationOnAtomicPart(AtomicPart *apart,
                Set<AtomicPart *> &setOfVisitedPartIds) const;
    };

    class NumTraversal2c : public NumTraversal1 {
        public:
            NumTraversal2c(DataHolder *dh) : NumTraversal1(TRAVERSAL, "T2c", dh) {
            }

            virtual int run(int tid) const;

        protected:
            virtual int performOperationOnAtomicPart(AtomicPart *apart,
                Set<AtomicPart *> &setOfVisitedPartIds) const;
    };

    class NumTraversal3a : public NumTraversal1 {
        protected:
            NumTraversal3a(optype t, const char *n, DataHolder *dh)
                : NumTraversal1(t, n, dh) {
            }

        public:
            NumTraversal3a(DataHolder *dh) : NumTraversal1(TRAVERSAL, "T3a", dh) {
            }

            virtual int run(int tid) const;

        protected:
            virtual int performOperationOnAtomicPart(AtomicPart *apart,
                Set<AtomicPart *> &setOfVisitedPartIds) const;

            void updateBuildDate(AtomicPart *apart) const;
    };

    class NumTraversal3b : public NumTraversal3a {
        public:
            NumTraversal3b(DataHolder *dh) : NumTraversal3a(TRAVERSAL, "T3b", dh) {
            }

        protected:
            virtual int performOperationOnAtomicPart(AtomicPart *apart,
                Set<AtomicPart *> &setOfVisitedPartIds) const;
    };

    class NumTraversal3c : public NumTraversal3a {
        public:
            NumTraversal3c(DataHolder *dh) : NumTraversal3a(TRAVERSAL, "T3c", dh) {
            }

        protected:
            virtual int performOperationOnAtomicPart(AtomicPart *apart,
                Set<AtomicPart *> &setOfVisitedPartIds) const;
    };

    class NumTraversal4 : public NumTraversal1 {
        protected:
            NumTraversal4(optype t, const char *n, DataHolder *dh)
                : NumTraversal1(t, n, dh) {
            }

        public:
            NumTraversal4(DataHolder *dh) : NumTraversal1(TRAVERSAL_RO, "T4", dh) {
            }

            virtual int run(int tid) const;

        protected:
            virtual int traverse(CompositePart *component) const;
            virtual int traverse(Document *doc) const;
            virtual int traverse(AtomicPart *part,
                Set<AtomicPart *> &setOfVisitedParts) const;
            virtual int performOperationOnAtomicPart(AtomicPart *apart,
                Set<AtomicPart *> &setOfVisitedPartIds) const;
    };

    class NumTraversal5 : public NumTraversal4 {
        public:
            NumTraversal5(DataHolder *dh) : NumTraversal4(TRAVERSAL, "T5", dh) {
            }

            virtual int run(int tid) const;

        protected:
            virtual int traverse(Document *doc) const;
    };

    class NumTraversal6 : public NumTraversal1 {
        public:
            NumTraversal6(DataHolder *dh) : NumTraversal1(TRAVERSAL_RO, "T6", dh) {
            }

        protected:
            // I made this shorter than in original bench
            virtual int traverse(CompositePart *component) const;
    };

    // following traversal is actually short traversal, but is here because
    // of it's slightly misleading name
    class NumTraversal7 : public Operation {
        protected:
            NumTraversal7(optype t, const char *n, DataHolder *dh)
                : Operation(t, n, dh) {
            }

        public:
            NumTraversal7(DataHolder *dh)
                : Operation(SHORT_TRAVERSAL_RO, "T7", dh) {
            }

            virtual int run(int tid) const;

        protected:
            int innerRun(int tid) const;
            int traverse(CompositePart *cpart) const;
            int traverse(Assembly *assembly,
                Set<Assembly *> &visitedAssemblies) const;
            virtual void performOperationOnAssembly(Assembly *assembly) const;
    };

    // following two traversals are actually ro operations, but are here
    // because of their slightly misleading names

    class NumTraversal8 : public Operation {
        protected:
            NumTraversal8(optype t, const char *n, DataHolder *dh)
                : Operation(t, n, dh) {
            }

        public:
            NumTraversal8(DataHolder *dh)
                : Operation(OPERATION_RO, "T8", dh) {
            }

            virtual int run(int tid) const;

        protected:
            virtual int traverse(Manual *manual) const;
    };

    class NumTraversal9 : public NumTraversal8 {
        public:
            NumTraversal9(DataHolder *dh)
                : NumTraversal8(OPERATION_RO, "T9", dh) {
            }

        protected:
            virtual int traverse(Manual *manual) const;
    };

}

#endif // SB7_Num_TRAVERSAL_OPS_
