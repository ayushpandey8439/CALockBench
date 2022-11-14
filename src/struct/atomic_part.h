//
// Created by Ayush Pandey on 15/11/2022.
//

#ifndef STMBENCH_ATOMIC_PART_H
#define STMBENCH_ATOMIC_PART_H


#include <utility>

#include "../containers.h"
#include "design_obj.h"

using namespace std;

namespace sb7 {

    class Connection;

    class CompositePart;

    class AtomicPart : public DesignObj {
    protected:
        typedef Set<Connection *> connection_set;

    public:
        AtomicPart(int id, string type, int buildDate, int x, int y)
                : DesignObj(id, std::move(type), buildDate), m_x(x), m_y(y),
                  m_to(new connection_set()), m_from(new connection_set()) {
        }

        ~AtomicPart() override {
            delete m_to;
            delete m_from;
        }

        void connectTo(AtomicPart *dest, const string &type, int len) const;

        void addConnectionFromOtherPart(Connection *conn) const {
            m_from->add(conn);
        }

        void removeConnectionFromOtherPart(Connection *conn) const {
            m_from->remove(conn);
        }

        void removeConnectionToOtherPart(Connection *conn) const {
            m_to->remove(conn);
        }

        void setCompositePart(CompositePart *cp) {
            m_partOf = cp;
        }

        /**
         * Return number of outgoing connections.
         */
        int getNumConnections() const {
            return m_to->size();
        }

        connection_set *getToConnections() const {
            return m_to;
        }

        connection_set *getFromConnections() const {
            return m_from;
        }

        CompositePart *getPartOf() const {
            return m_partOf;
        }

        void swapXY() {
            int tmp = m_y;
            m_y = m_x;
            m_x = tmp;
        }

        int getX() const {
            return m_x;
        }

        int getY() const {
            return m_y;
        }

    private:
        int m_x, m_y;
        connection_set *m_to, *m_from;
        CompositePart *m_partOf{};
    };

}

#endif //STMBENCH_ATOMIC_PART_H
