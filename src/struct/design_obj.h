//
// Created by Ayush Pandey on 15/11/2022.
//

#ifndef STMBENCH_DESIGN_OBJ_H
#define STMBENCH_DESIGN_OBJ_H


#include <string>
#include <utility>
#include <utility>
#include "vector"
#include "list"
#include "set"
#include "unordered_set"

using namespace std;

namespace sb7 {
    class DesignObj {
    public:
        DesignObj(int id, string type, int buildDate)
                : m_id(id), m_type(std::move(std::move(type))), m_buildDate(buildDate) {
            m_pre_number = 0;
            m_post_number = 0;
            pthread_rwlock_init(&NodeLock, NULL);
            hasLabel= false;
        }



        virtual ~DesignObj() = default;

        int getId() const {
            return m_id;
        }

        string getStringId() const{
            return pathLabel.back();
        }

        void setPathLabel(const list<string>& label){
            hasLabel=true;
            pathLabel.clear();
            pathLabel = label;
            criticalAncestors.clear();
            for(const auto& d: label){
                criticalAncestors.insert(d);
            }
        }

        int getBuildDate() const {
            return m_buildDate;
        }

        void updateBuildDate();

        void nullOperation() const {}

        int m_pre_number;
        int m_post_number;
        pthread_rwlock_t NodeLock;
        bool hasLabel;
        list<string> pathLabel;
        unordered_set<string> criticalAncestors;
    protected:
        int m_id;
        string m_type;
        int m_buildDate;



    };
}


#endif //STMBENCH_DESIGN_OBJ_H
