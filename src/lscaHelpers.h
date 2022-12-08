//
// Created by Ayush Pandey on 21/11/2022.
//


#ifndef STMBENCH_LSCAHELPERS_H
#define STMBENCH_LSCAHELPERS_H
#include <string>
#include <list>
#include "./struct/design_obj.h"
#include "data_holder.h"

using namespace std;
using namespace sb7;

class lscaHelpers {

public:
    static bool hasCriticalAncestor(unordered_set<int> * A, int d){
        if(!A->empty() && A->find(d)!=A->end()){
            return true;
        }
        else return false;
    }

    static DesignObj * getLockObject(list<int> objectLabel, sb7::DataHolder * dh){
        int objectId;
        if(objectLabel.size()==1){
            objectId = objectLabel.front();
        } else {
            objectId = objectLabel.back();
        }
        int typeIdentifier = objectId%10;
        int id = objectId/10;
        switch(typeIdentifier){
            case 1:
                return dh->getComplexAssembly(id);
            case 2:
                return dh->getBaseAssembly(id);
            case 3:
                return dh->getCompositePart(id);
            case 4: {
                sb7::Map<int, sb7::AtomicPart *> *index = dh->getAtomicPartIdIndex();
                sb7::Map<int, sb7::AtomicPart *>::Query query;
                query.key = id;
                index->get(query);
                return query.val;
            }
            default:
                return nullptr;
        }
    }
};


#endif //STMBENCH_LSCAHELPERS_H
