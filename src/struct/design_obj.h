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

        void setPathLabel(list<DesignObj*> label){
            hasLabel=true;
            pathLabel = label;
            for(auto * d: label){
                criticalAncestors.insert(d);
            }
        }

        bool hasCriticalAncestor(DesignObj* d){
            if(criticalAncestors.find(d)!=criticalAncestors.end()){
                return true;
            }
            else return false;
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
        list<DesignObj*> pathLabel;
        unordered_set<DesignObj*> criticalAncestors;
    protected:
        int m_id;
        string m_type;
        int m_buildDate;



    };
}


#endif //STMBENCH_DESIGN_OBJ_H
