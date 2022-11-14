#include "design_obj.h"

void sb7::DesignObj::updateBuildDate() {
    if (m_buildDate % 2 == 0) {
        m_buildDate--;
    } else {
        m_buildDate++;
    }
}
