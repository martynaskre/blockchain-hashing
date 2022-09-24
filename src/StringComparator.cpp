//
// Created by Martynas Skrebė on 2022-09-24.
//

#include "StringComparator.h"
#include <vector>

double StringComparator::calculateDifference(const std::string &first, const std::string &second) {
    if ((first.length() == 0 && second.length() == 0) || (first == second)) {
        return 0;
    }

    unsigned int stepsToReproduce = calculateLevenshteinDistance(first, second);

    return ((double) stepsToReproduce / std::max(first.length(), second.length())) * 100;
}

unsigned int StringComparator::bitDifference(const std::string &first, const std::string &second) {
    int differentChars = 0;

    for (std::string::size_type i = 0; i < first.size(); i++) {
        if (first[i] != second[i]) {
            differentChars++;
        }
    }

    // a char consumes 8 bits, so every character difference equals to 8 bits
    return differentChars * 8;
}

unsigned int StringComparator::calculateLevenshteinDistance(const std::string &first, const std::string &second) {
    const std::size_t len1 = first.size(), len2 = second.size();
    std::vector<std::vector<unsigned int>> d(len1 + 1, std::vector<unsigned int>(len2 + 1));

    d[0][0] = 0;
    for(unsigned int i = 1; i <= len1; ++i) d[i][0] = i;
    for(unsigned int i = 1; i <= len2; ++i) d[0][i] = i;

    for(unsigned int i = 1; i <= len1; ++i)
        for(unsigned int j = 1; j <= len2; ++j)
            d[i][j] = std::min({ d[i - 1][j] + 1, d[i][j - 1] + 1, d[i - 1][j - 1] + (first[i - 1] == second[j - 1] ? 0 : 1) });

    return d[len1][len2];
}
