//
// Created by Ayush Pandey on 15/11/2022.
//

#ifndef STMBENCH_HELPERS_H
#define STMBENCH_HELPERS_H

#include <iostream>

#define MAX_INT_LEN 65
#define HUNDRED_PERCENT 100

#define ITOA(itoa_buf, i)                        \
    char itoa_buf[MAX_INT_LEN];                    \
    snprintf(itoa_buf, MAX_INT_LEN, "%d", i);

namespace sb7 {

    void printSection(std::ostream &out, const char *text);

    std::string boolToStr(bool val);

    int strToBool(const std::string &str);

    bool equalNoCase(const std::string &s1, const std::string &s2);

    int strToUint(const std::string &str);

    const int line_width = 78;
    const char section_fill_char = '-';
}


#endif //STMBENCH_HELPERS_H
