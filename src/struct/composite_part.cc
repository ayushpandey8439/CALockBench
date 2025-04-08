#include "atomic_part.h"
#include "composite_part.h"
#include "document.h"

using namespace std;

bool sb7::CompositePart::addPart(AtomicPart *apart) {
    bool add = m_parts->add(apart);

    if (add) {
        apart->setCompositePart(this);

        if (m_rootPart == NULL) {
            m_rootPart = apart;
        }
    }

    return add;
}
