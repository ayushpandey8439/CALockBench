//
// Created by Ayush Pandey on 15/11/2022.
//

#ifndef STMBENCH_CONNECTION_H
#define STMBENCH_CONNECTION_H


#include <utility>
#include "string"

namespace sb7 {

    class AtomicPart;

    class Connection {
    public:
        Connection(AtomicPart *from, AtomicPart *to,
                   std::string type, int length)
                : m_type(std::move(type)), m_length(length), m_from(from), m_to(to) {
        }

        virtual ~Connection() = default;

        Connection *getReversed() const {
            return new Connection(m_to, m_from, m_type, m_length);
        }

        AtomicPart *getDestination() const {
            return m_to;
        }

        AtomicPart *getSource() const {
            return m_from;
        }

    private:
        std::string m_type;
        int m_length;
        AtomicPart *m_from;
        AtomicPart *m_to;
    };
}

#endif //STMBENCH_CONNECTION_H
