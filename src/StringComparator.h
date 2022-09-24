//
// Created by Martynas Skrebė on 2022-09-24.
//

#ifndef BLOCKCHAIN_STRINGCOMPARATOR_H
#define BLOCKCHAIN_STRINGCOMPARATOR_H


#include <string>

class StringComparator {
public:
    // "aa" differs from "aaa" by 33%
    static double calculateDifference(const std::string &first, const std::string &second);
    static unsigned int bitDifference(const std::string &first, const std::string &second);
private:
    static unsigned int calculateLevenshteinDistance(const std::string &first, const std::string &second);
};


#endif //BLOCKCHAIN_STRINGCOMPARATOR_H
