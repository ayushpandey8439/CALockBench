#ifndef SB7_Mid_TRAVERSAL_OPS_
#define SB7_Mid_TRAVERSAL_OPS_

#include "../operations.h"
#include "../../containers.h"
#include "../../struct/assembly.h"

namespace sb7 {
    class MidTraversal1 : public Operation {
        protected:
            MidTraversal1(optype t, const char *n, DataHolder *dh)
                : Operation(t, n, dh) {
            }

        public:
            MidTraversal1(DataHolder *dh) : Operation(TRAVERSAL_RO, "T1", dh) {
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

    class MidTraversal2a : public MidTraversal1 {
        public:
            MidTraversal2a(DataHolder *dh) : MidTraversal1(TRAVERSAL, "T2a", dh) {
            }

            virtual int run(int tid) const;

        protected:
            virtual int performOperationOnAtomicPart(AtomicPart *apart,
                Set<AtomicPart *> &setOfVisitedPartIds) const;
    };

    class MidTraversal2b : public MidTraversal1 {
        public:
            MidTraversal2b(DataHolder *dh) : MidTraversal1(TRAVERSAL, "T2b", dh) {
            }

            virtual int run(int tid) const;

        protected:
            virtual int performOperationOnAtomicPart(AtomicPart *apart,
                Set<AtomicPart *> &setOfVisitedPartIds) const;
    };

    class MidTraversal2c : public MidTraversal1 {
        public:
            MidTraversal2c(DataHolder *dh) : MidTraversal1(TRAVERSAL, "T2c", dh) {
            }

            virtual int run(int tid) const;

        protected:
            virtual int performOperationOnAtomicPart(AtomicPart *apart,
                Set<AtomicPart *> &setOfVisitedPartIds) const;
    };

    class MidTraversal3a : public MidTraversal1 {
        protected:
            MidTraversal3a(optype t, const char *n, DataHolder *dh)
                : MidTraversal1(t, n, dh) {
            }

        public:
            MidTraversal3a(DataHolder *dh) : MidTraversal1(TRAVERSAL, "T3a", dh) {
            }

            virtual int run(int tid) const;

        protected:
            virtual int performOperationOnAtomicPart(AtomicPart *apart,
                Set<AtomicPart *> &setOfVisitedPartIds) const;

            void updateBuildDate(AtomicPart *apart) const;
    };

    class MidTraversal3b : public MidTraversal3a {
        public:
            MidTraversal3b(DataHolder *dh) : MidTraversal3a(TRAVERSAL, "T3b", dh) {
            }

        protected:
            virtual int performOperationOnAtomicPart(AtomicPart *apart,
                Set<AtomicPart *> &setOfVisitedPartIds) const;
    };

    class MidTraversal3c : public MidTraversal3a {
        public:
            MidTraversal3c(DataHolder *dh) : MidTraversal3a(TRAVERSAL, "T3c", dh) {
            }

        protected:
            virtual int performOperationOnAtomicPart(AtomicPart *apart,
                Set<AtomicPart *> &setOfVisitedPartIds) const;
    };

    class MidTraversal4 : public MidTraversal1 {
        protected:
            MidTraversal4(optype t, const char *n, DataHolder *dh)
                : MidTraversal1(t, n, dh) {
            }

        public:
            MidTraversal4(DataHolder *dh) : MidTraversal1(TRAVERSAL_RO, "T4", dh) {
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

    class MidTraversal5 : public MidTraversal4 {
        public:
            MidTraversal5(DataHolder *dh) : MidTraversal4(TRAVERSAL, "T5", dh) {
            }

            virtual int run(int tid) const;

        protected:
            virtual int traverse(Document *doc) const;
    };

    class MidTraversal6 : public MidTraversal1 {
        public:
            MidTraversal6(DataHolder *dh) : MidTraversal1(TRAVERSAL_RO, "T6", dh) {
            }

        protected:
            // I made this shorter than in original bench
            virtual int traverse(CompositePart *component) const;
    };

    // following traversal is actually short traversal, but is here because
    // of it's slightly misleading name
    class MidTraversal7 : public Operation {
        protected:
            MidTraversal7(optype t, const char *n, DataHolder *dh)
                : Operation(t, n, dh) {
            }

        public:
            MidTraversal7(DataHolder *dh)
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

    class MidTraversal8 : public Operation {
        protected:
            MidTraversal8(optype t, const char *n, DataHolder *dh)
                : Operation(t, n, dh) {
            }

        public:
            MidTraversal8(DataHolder *dh)
                : Operation(OPERATION_RO, "T8", dh) {
            }

            virtual int run(int tid) const;

        protected:
            virtual int traverse(Manual *manual) const;
    };

    class MidTraversal9 : public MidTraversal8 {
        public:
            MidTraversal9(DataHolder *dh)
                : MidTraversal8(OPERATION_RO, "T9", dh) {
            }

        protected:
            virtual int traverse(Manual *manual) const;
    };

}

#endif // SB7_Mid_TRAVERSAL_OPS_
