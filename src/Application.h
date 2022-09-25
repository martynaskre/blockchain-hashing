//
// Created by Martynas Skrebė on 2022-09-20.
//

#ifndef BLOCKCHAIN_APPLICATION_H
#define BLOCKCHAIN_APPLICATION_H


#include <string>
#include <fstream>
#include "Hash.h"
#include "StringGenerator.h"

class Application {
    std::ifstream reader;
    std::ofstream writer;
    class Hash hash;
    StringGenerator generator;
    static const std::vector<std::pair<std::string, std::string>> commands;

public:
    void run(int argc, char *argv[]);

private:
    void printHelp();
    void hashInput(const std::string &input);
    void hashFile(const std::string &filename);
    void generateFiles();
    void performBenchmark(const std::string &filename);
    void performCollisionTest();
    void performAvalancheTest();
};


#endif //BLOCKCHAIN_APPLICATION_H
