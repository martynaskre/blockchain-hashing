//
// Created by Martynas Skrebė on 2022-09-24.
//

#ifndef BLOCKCHAIN_TESTER_H
#define BLOCKCHAIN_TESTER_H


#include <string>
#include <random>
#include <iostream>
#include <map>
#include <vector>
#include <iterator>
#include "StringGenerator.h"
#include "Hash.h"

using std::cout;
using std::endl;
using std::map;
using std::pair;
using std::string;
using std::vector;

typedef string hashVal;
typedef vector<string> originalVal;

class Tester
{
public:
    void runTests(size_t count, size_t symbolCount, string resFileName);

private:
    map<hashVal, originalVal> hashes;
    map<hashVal, originalVal> collisions;

    StringGenerator gen;
    class Hash hasher;
    bool testCollisions(string resFileName);
    void generateStringsAndHashes(size_t count, size_t symbolCount);
};


#endif //BLOCKCHAIN_TESTER_H
