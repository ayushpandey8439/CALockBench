#include "assembly.h"
#include "composite_part.h"

#include "../parameters.h"

// ComplexAssembly implementation
void sb7::ComplexAssembly::setLevel() {
    if (m_superAssembly != NULL) {
        m_level = m_superAssembly->m_level - 1;
    } else {
        //
        // TODO do this in a nicer way
        //
        m_level = parameters.getNumAssmLevels();
    }
}

bool sb7::ComplexAssembly::addSubAssembly(Assembly *assembly) const {
    return m_subAssemblies->add(assembly);
}

bool sb7::ComplexAssembly::removeSubAssembly(Assembly *assembly) const {
    return m_subAssemblies->remove(assembly);
}

// BaseAssembly implementation
void sb7::BaseAssembly::addComponent(CompositePart *cpart) const {
    if (m_components->add(cpart)) {
        cpart->addAssembly((BaseAssembly *) this);
    }
}

bool sb7::BaseAssembly::removeComponent(CompositePart *cpart) const {
    bool ret = m_components->remove(cpart);

    if (ret) {
        cpart->removeAssembly((BaseAssembly *) this);
    }

    return ret;
}
