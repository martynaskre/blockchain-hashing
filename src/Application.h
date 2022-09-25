//
// Created by Martynas Skrebė on 2022-09-20.
//

#ifndef BLOCKCHAIN_APPLICATION_H
#define BLOCKCHAIN_APPLICATION_H


#include <string>
#include <fstream>

enum ApplicationMode {
    Hash,
    GenerateFile,
};

class Application {
    ApplicationMode mode;
    std::ifstream reader;
    std::ofstream writer;
    static const std::vector<std::pair<std::string, std::string>> commands;

public:
    void run(int argc, char *argv[]);
private:
    std::string makeHash();
    void printHelp();
    void generateFiles();
    void performBenchmark();
    void performCollisionTest();
    void performAvalancheTest();
};


#endif //BLOCKCHAIN_APPLICATION_H
