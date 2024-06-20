#ifndef SB7_DESIGN_OBJ_H_
#define SB7_DESIGN_OBJ_H_

#include <string>
#include <list>
#include "boost/container/flat_set.hpp"
#include "boost/container/list.hpp"

using namespace std;

namespace sb7 {
    class DesignObj {
    public:
        DesignObj(int id, string type, int buildDate)
                : m_id(id), m_type(type), m_buildDate(buildDate) {
            m_pre_number = 0;
            m_post_number = 0;
            pthread_rwlock_init(&NodeLock, NULL);
//*********************************************************************************************
            rlm_pre_number = 0;
            rlm_post_number = 0;
        }

        virtual ~DesignObj() {}

        int getId() const {
            return m_id;
        }

        int getLabellingId() const {
            return pathLabel.back();
        }

        int getLSCA() const {
            if (pathLabel.size() == 1) {
                return *(--pathLabel.rbegin());
            } else {
                return *pathLabel.rbegin();
            }
        }

        void Delete() {
            this->isDeleted = true;
            this->hasLabel = false;
            this->m_id = -1;
            //this->criticalAncestors.clear();
            // this->pathLabel = std::list<int>();
            this->m_buildDate = -1;
            this->m_type.clear();
            m_post_number = 0;
            m_pre_number = 0;
        }

        void setPathLabel(const list<int> label) {
            hasLabel = true;
            //pathLabel.clear();
            pathLabel = label;
            criticalAncestors.clear();
            for (const auto &d: label) {
                criticalAncestors.insert(d);
            }
        }

        string getPathLabel() {
            string labelString;
            for (auto i: pathLabel) {
                labelString += to_string(i) + ", ";
            }
            labelString.pop_back();
            labelString.pop_back();
            return labelString;

        }

        int getBuildDate() const {
            return m_buildDate;
        }

        void updateBuildDate();

        void nullOperation() const {}

        long int m_pre_number;
        long int m_post_number;
        int rlm_pre_number;
        int rlm_post_number;
        pthread_rwlock_t NodeLock;
        bool hasLabel;
        list<int> pathLabel{};
        boost::container::flat_set<int> criticalAncestors;
        bool isDeleted;

    protected:
        int m_id;
        string m_type;
        int m_buildDate;
    };
}

#endif /*SB7_DESIGN_OBJ_H_*/
