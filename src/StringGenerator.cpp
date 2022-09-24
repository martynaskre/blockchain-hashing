//
// Created by Martynas Skrebė on 2022-09-20.
//

#include <sstream>
#include "StringGenerator.h"

const std::string ABC = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

std::random_device StringGenerator::rd;
std::mt19937 StringGenerator::mt(StringGenerator::rd());
std::uniform_int_distribution<int> StringGenerator::dist(0, ABC.length());

StringGenerator &StringGenerator::setLength(StringGenerator::int64 len) {
    length = len;

    return *this;
}

std::string StringGenerator::generate() {
    std::stringstream result;

    for (int i = 0; i < length; i++) {
        result << ABC[dist(mt)];
    }

    return result.str();
}
