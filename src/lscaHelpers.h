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
    static vector<DesignObj*> findLSCA(vector<DesignObj*> label1, vector<DesignObj*> label2){
        vector<DesignObj*> common;
        set_intersection(label1.begin(), label1.end(),
                         label2.begin(), label2.end(),
                         back_inserter(common));
        return common;
    }
};


#endif //STMBENCH_LSCAHELPERS_H
