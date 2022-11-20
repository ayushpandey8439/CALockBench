//
// Created by Ayush Pandey on 15/11/2022.
//

#ifndef STMBENCH_DESIGN_OBJ_H
#define STMBENCH_DESIGN_OBJ_H


#include <string>
#include <utility>
#include <utility>
#include "list"
#include "set"

using namespace std;

namespace sb7 {
    class DesignObj {
    public:
        DesignObj(int id, string type, int buildDate)
                : m_id(id), m_type(std::move(std::move(type))), m_buildDate(buildDate) {
            pthread_rwlock_init(&NodeLock, NULL);
        }


        pthread_rwlock_t NodeLock;

        virtual ~DesignObj() = default;

        int getId() const {
            return m_id;
        }

        list<string> getPathLabel(){
            return pathLabel;
        }
        void setPathLabel(list<string> label){
            pathLabel = label;
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
        list<std::string> pathLabel;
    };
}


#endif //STMBENCH_DESIGN_OBJ_H
