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
#include <thread>


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
            isDeleted = false;
            pathLabel={};
        }



        virtual ~DesignObj() = default;

        int getId() const {
            return m_id;
        }

        int getLabellingId() const{
            return pathLabel.back();
        }

        void Delete() {
            this->isDeleted = true;
            this->hasLabel = false;
            this->m_id = -1;
            //this->criticalAncestors.clear();
            this->pathLabel = std::list<int>();
            this->m_buildDate = -1;
            this->m_type.clear();
            m_post_number=0;
            m_pre_number=0;
        }

        void setPathLabel(const list<int>& label){
            hasLabel=true;
            //pathLabel.clear();
            pathLabel = label;
            criticalAncestors.clear();
            for(const auto& d: label){
                criticalAncestors.push_back(d);
            }
        }

        int getBuildDate() const {
            return m_buildDate;
        }

        void updateBuildDate();

        void nullOperation() const {}

        long int m_pre_number;
        long int m_post_number;
        pthread_rwlock_t NodeLock;
        bool hasLabel;
        list<int> pathLabel{};
        vector<int> criticalAncestors;
        bool isDeleted;
    protected:
        int m_id;
        string m_type;
        int m_buildDate;



    };
}


#endif //STMBENCH_DESIGN_OBJ_H
