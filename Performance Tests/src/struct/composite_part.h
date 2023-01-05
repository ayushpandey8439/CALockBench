//
// Created by Ayush Pandey on 15/11/2022.
//

#ifndef STMBENCH_COMPOSITE_PART_H
#define STMBENCH_COMPOSITE_PART_H


#include <utility>

#include "../containers.h"
#include "design_obj.h"
#include "assembly.h"
#include "document.h"

using namespace std;

namespace sb7 {

    class Document;

    class AtomicPart;

    class CompositePart : public DesignObj {
    protected:
        typedef Set<BaseAssembly *> base_assembly_bag;
        typedef Set<AtomicPart *> atomic_part_set;

    public:
        CompositePart(int id, string type, int buildDate,
                      Document *doc)
                : DesignObj(id, std::move(type), buildDate), m_doc(doc),
                  m_usedIn(new base_assembly_bag()),
                  m_parts(new atomic_part_set()),
                  m_rootPart(nullptr) {
            setDocumentPart();
        }

        ~CompositePart() override {
            delete m_usedIn;
            delete m_parts;
        }

        void addAssembly(BaseAssembly * assembly) const {
            m_usedIn->add(assembly);
        }

        void removeAssembly(BaseAssembly *assembly) const {
            m_usedIn->remove(assembly);
        }

        bool addPart(AtomicPart *part);

        AtomicPart *getRootPart() const {
            return m_rootPart;
        }

        Document *getDocumentation() const {
            return m_doc;
        }

        atomic_part_set *getParts() const {
            return m_parts;
        }

        base_assembly_bag *getUsedIn() const {
            return m_usedIn;
        }

    private:
        void setDocumentPart() const {
            m_doc->setPart((CompositePart *) this);
        }

    private:
        Document *m_doc;
        base_assembly_bag *m_usedIn;
        atomic_part_set *m_parts;
        AtomicPart *m_rootPart;
    };
}

#endif //STMBENCH_COMPOSITE_PART_H
