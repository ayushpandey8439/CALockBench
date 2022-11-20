//
// Created by Ayush Pandey on 21/11/2022.
//


#ifndef STMBENCH_LSCAHELPERS_H
#define STMBENCH_LSCAHELPERS_H
#include <string>
#include <list>
using namespace std;

class lscaHelpers {

public:
    static list<string> findLSCA(list<string> label1, list<string> label2){
        list<string> common;
        set_intersection(label1.begin(), label1.end(),
                         label2.begin(), label2.end(),
                         back_inserter(common));
        return common;
    }
};


#endif //STMBENCH_LSCAHELPERS_H
