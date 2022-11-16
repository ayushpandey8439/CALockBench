//
// Created by Ayush Pandey on 15/11/2022.
//

#ifndef STMBENCH_DESIGN_OBJ_H
#define STMBENCH_DESIGN_OBJ_H


#include <string>
#include <utility>
#include <utility>
#include "vector"
#include "set"

using namespace std;

namespace sb7 {
    class DesignObj {
    public:
        DesignObj(int id, string type, int buildDate)
                : m_id(id), m_type(std::move(std::move(type))), m_buildDate(buildDate) {
            pthread_rwlock_init(&NodeLock, NULL);
        }

        vector<std::string> pathLabel;
        set<string> labelNodes;
        pthread_rwlock_t NodeLock;

        virtual ~DesignObj() = default;

        int getId() const {
            return m_id;
        }

        int getBuildDate() const {
            return m_buildDate;
        }

        void updateBuildDate();

        void nullOperation() const {}

    protected:
        int m_id;
        string m_type;
        int m_buildDate;
    };
}


#endif //STMBENCH_DESIGN_OBJ_H
