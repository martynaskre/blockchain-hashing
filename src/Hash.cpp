//
// Created by Martynas Skrebė on 2022-09-15.
//

#include "Hash.h"

#include <utility>
#include <sstream>

const int LENGTH = 64;

Hash::Hash() = default;

Hash::Hash(std::string str) : string(std::move(str)) {};

Hash::Hash(char *str) : string(str) {}

Hash &Hash::setString(std::string str) {
    string = std::move(str);

    return *this;
};

Hash &Hash::setString(char *str) {
    string = str;

    return *this;
}

std::string Hash::make() {
    std::stringstream output;

    for (int i = 0; i < LENGTH; i++) {
        char character = i ^ string[0];

        output << std::hex << character;
    }

    return output.str();
}
