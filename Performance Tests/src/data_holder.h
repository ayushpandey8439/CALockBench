//
// Created by Ayush Pandey on 15/11/2022.
//

#ifndef STMBENCH_DATA_HOLDER_H
#define STMBENCH_DATA_HOLDER_H


#include <string>

#include "containers.h"
#include "id_pool.h"

#include "struct/module.h"
#include "struct/atomic_part.h"
#include "struct/document.h"
#include "struct/composite_part.h"
#include "struct/assembly.h"

using namespace std;

namespace sb7 {

    /**
     * DataHolder object is a place to find sb7 data structure used in
     * the benchmark. It also provides high level functions for manipulating
     * objects that are used in the benchmark.
     */
    class DataHolder {
    protected:
        // typedef shortcuts
        typedef Map<int, AtomicPart *> atomic_part_int_index;
        typedef Set<AtomicPart *> atomic_part_set;
        typedef Map<int, atomic_part_set *> atomic_part_set_int_index;
        typedef Map<string, Document *> document_string_index;
        typedef Map<int, CompositePart *> composite_part_int_index;
        typedef Map<int, BaseAssembly *> base_assembly_int_index;
        typedef Map<int, ComplexAssembly *> complex_assembly_int_index;

    public:
        DataHolder() = default;

        virtual ~DataHolder();

        /**
         * Initialization of the whole structure.
         */
        void init();

        // getters for indexes and module
        atomic_part_set_int_index *getAtomicPartBuildDateIndex() {
            return m_atomicPartBuildDateIndex;
        }

        atomic_part_int_index *getAtomicPartIdIndex() {
            return m_atomicPartIdIndex;
        }

        base_assembly_int_index *getBaseAssemblyIdIndex() {
            return m_baseAssemblyIdIndex;
        }

        complex_assembly_int_index *getComplexAssemblyIdIndex() {
            return m_complexAssemblyIdIndex;
        }

        composite_part_int_index *getCompositePartIdIndex() {
            return m_compositePartIdIndex;
        }

        document_string_index *getDocumentTitleIndex() {
            return m_documentTitleIndex;
        }

        Module *getModule() {
            return m_module;
        }

    private:
        void allocateData();

        // TODO maybe inline this to reduce copying data around
        static string createText(unsigned size, const string &txt);

        static string createType();

        static int createBuildDate(int min, int max);

        void createCompositeParts(CompositePart *designLibrary[],
                                  int dlSize);

        void createAtomicParts(AtomicPart *parts[], int psize,
                               CompositePart *cpart);

        AtomicPart *createAtomicPart();

        void createConnections(AtomicPart *parts[], int size, int outConn);

        void connectAtomicParts(AtomicPart *ps, AtomicPart *pe);

        static int generateConnectionLength();

        Module *createModule();

        ComplexAssembly *createAssemblies();

        ComplexAssembly *createComplexAssembly(ComplexAssembly *parent,
                                               int childNum);

        void connectAssembliesParts(CompositePart *designLibrary[],
                                    int partNum, int connNum);

        Document *createDocument(int cpartId);

        Manual *createManual(int moduleId);

        //////////////////////////////////////////////////////////////////////
        // Some functions that are used outside of data holder, but is good //
        // to have them defined in one place.                               //
        //////////////////////////////////////////////////////////////////////

        // TODO as operations are just functions that operate on data
        // encapsulated in data holder, would it be more natural to make
        // them part of this class as well?
        // Maybe, but when they are moved to separate class we have benefit
        // of oo features (inheritance most notably)

    public:
        void addAtomicPartToBuildDateIndex(AtomicPart *apart);

        void removeAtomicPartFromBuildDateIndex(AtomicPart *apart);

        CompositePart *createCompositePart();

        void deleteCompositePart(CompositePart *cpart);

        void createBaseAssembly(ComplexAssembly *parent);

        void deleteBaseAssembly(BaseAssembly *bassm);

        void createSubAssembly(ComplexAssembly *parent,
                               int childNum);

        void deleteComplexAssembly(ComplexAssembly *bassm);

    protected:
        void deleteDocument(Document *doc);

        void deleteAtomicPart(AtomicPart *apart);

        ////////////////////////////////////////////////////////////////
        // Here are some functions for searching objects belonging to //
        // different classes in indexes.                              //
        ////////////////////////////////////////////////////////////////

    public:
        CompositePart *getCompositePart(int id) const;

        BaseAssembly *getBaseAssembly(int id) const;

        ComplexAssembly *getComplexAssembly(int id) const;

    private:
        /**
         * The only module used in the data structure.
         */
        Module *m_module{};

        // definition of indexes
        atomic_part_int_index *m_atomicPartIdIndex{};
        atomic_part_set_int_index *m_atomicPartBuildDateIndex{};
        document_string_index *m_documentTitleIndex{};
        composite_part_int_index *m_compositePartIdIndex{};
        base_assembly_int_index *m_baseAssemblyIdIndex{};
        complex_assembly_int_index *m_complexAssemblyIdIndex{};

        // id pools
        IdPool *m_compositePartIdPool{};
        IdPool *m_atomicPartIdPool{};
        IdPool *m_moduleIdPool{};
        IdPool *m_documentIdPool{};
        IdPool *m_manualIdPool{};
        IdPool *m_baseAssemblyIdPool{};
        IdPool *m_complexAssemblyIdPool{};
    };
}


#endif //STMBENCH_DATA_HOLDER_H
