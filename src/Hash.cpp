//
// Created by Martynas Skrebė on 2022-09-15.
//

#include "Hash.h"

#include <utility>
#include <sstream>

const int LENGTH = 64;
const std::string ABC = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!@#$%&";

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

    int characterSum = 0;

    for (char character: string) {
        characterSum += character ^ rotateRight(character, character);
    }

    std::stringstream characterSumArray;
    characterSumArray << characterSum;

    for (int i = 0; i < LENGTH; i++) {
        int charIndex;

        if (characterSumArray.str().length() > i) {
            charIndex = characterSumArray.str()[i] * i;
        } else {
            charIndex = characterSumArray.str()[i % characterSumArray.str().length()] * i;
        }

        if (charIndex >= ABC.length()) {
            charIndex = charIndex % ABC.length();
        }

        output << ABC[charIndex];
    }

    return output.str();
}

unsigned int Hash::rotateRight(int toRotate, int rotateBy) {
    return (toRotate >> rotateBy) | (toRotate << (32 - rotateBy));
}
