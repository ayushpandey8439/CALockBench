//
// Created by Ayush Pandey on 21/11/2022.
//


#ifndef STMBENCH_LSCAHELPERS_H
#define STMBENCH_LSCAHELPERS_H
#include <string>
#include <list>
#include "./struct/design_obj.h"

using namespace std;
using namespace sb7;

class lscaHelpers {

public:
    static DesignObj* findLSCA(DesignObj* v1, DesignObj* v2){
        for(auto *d: v1->pathLabel){
            if(v2->criticalAncestors.find(d) != v2->criticalAncestors.end()){
                return d;
            }
        }
        return v1->pathLabel.front(); //If this is a connected component, then front is always the root.
    }
};


#endif //STMBENCH_LSCAHELPERS_H
