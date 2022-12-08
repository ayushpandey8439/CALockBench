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
    static bool hasCriticalAncestor(unordered_set<string> A, string d){
        if(!A.empty() && A.find(d)!=A.end()){
            return true;
        }
        else return false;
    }

    static DesignObj * getLockObject(list<string> objectLabel, sb7::DataHolder * dh){
        string objectId;
        if(objectLabel.size()==1){
            objectId = objectLabel.front();
        } else {
            objectId = objectLabel.back();
        }
        string typeIdentifier = objectId.substr(0,2);
        string id = objectId.substr(2);
        if(typeIdentifier == "ca"){
            sb7::ComplexAssembly * ca = dh->getComplexAssembly(stoi(id));
            return ca;
        } else if(typeIdentifier == "ba") {
            sb7::BaseAssembly * ba = dh->getBaseAssembly(stoi(id));
            return ba;
        } else if(typeIdentifier == "cp"){
            sb7::CompositePart * cp  = dh->getCompositePart(stoi(id));
            return cp;
        } else if(typeIdentifier == "ap"){
            sb7::Map<int, sb7::AtomicPart *> * index  = dh->getAtomicPartIdIndex();
            sb7::Map<int, sb7::AtomicPart *>::Query query;
            query.key = stoi(id);
            index->get(query);
            return query.val;
        } else {
            return nullptr;
        }
    }
};


#endif //STMBENCH_LSCAHELPERS_H
