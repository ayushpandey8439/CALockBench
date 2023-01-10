//
// Created by Ayush Pandey on 21/11/2022.
//


#ifndef STMBENCH_LSCAHELPERS_H
#define STMBENCH_LSCAHELPERS_H
#include <string>
#include <list>
#include <algorithm>    // std::find
#include "./struct/design_obj.h"
#include "data_holder.h"

using namespace std;
using namespace sb7;

class lscaHelpers {

public:
    static bool hasCriticalAncestor(unordered_set<int> * A, int d){
        if(!A->empty() && A->find(d) !=A->end()){
            return true;
        }
        else return false;
    }

    static pair<DesignObj *, bool> getLockObject(list<int> *objectLabel, sb7::DataHolder * dh){
        pair<DesignObj *, bool> res;
        int objectId;
        if(objectLabel->size()==1){
            objectId = objectLabel->front();
        } else {
            objectId = objectLabel->back();
        }
        int typeIdentifier = objectId%10;
        int id = objectId/10;
        switch(typeIdentifier){
            case 1:
                res.first=dh->getComplexAssembly(id);
                res.second = true;
                return res;
            case 2:
                res.second = true;
                res.first= dh->getBaseAssembly(id);
                return res;
            case 3:
                res.second = true;
                res.first=  dh->getCompositePart(id);
                return res;
            case 4: {
                sb7::Map<int, sb7::AtomicPart *> *index = dh->getAtomicPartIdIndex();
                sb7::Map<int, sb7::AtomicPart *>::Query query;
                query.key = id;
                index->get(query);
                res.second = true;
                res.first=  query.val;
                return res;
            }
            default:
                res.first = nullptr;
                res.second = false;
                return res;
        }
    }
};


#endif //STMBENCH_LSCAHELPERS_H
