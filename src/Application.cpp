//
// Created by Martynas Skrebė on 2022-09-20.
//

#include "Application.h"
#include "iostream"
#include "Hash.h"
#include "StringGenerator.h"
#include "Benchmark.h"
#include "StringComparator.h"
#include "Tester.h"
#include "Color.h"

const std::vector<std::pair<std::string, std::string>> Application::commands = {
        {"--help", "Shows available commands"},
        {"--i {string}", "Hashes provided string"},
        {"--if {file_path}", "Hashes provided file contents"},
        {"--g", "Generates test files"},
        {"--b", "Runs benchmarks with generated files"},
        {"--c", "Runs collision test"},
        {"--a", "Runs avalanche test"}
};

void Application::run(int argc, char *argv[]) {
    if (argc <= 1) {
        std::cout << Color::RED << "No arguments were specified." << Color::RESET << std::endl << std::endl;

        this->printHelp();

        return;
    }

    std::vector<std::string> args(argv + 1, argv + argc);

    if ((args[0] == "--help" || args[0] == "--h" || args[0] == "-h" || args[0] == "--help") && argc == 2) {
        this->printHelp();

        return;
    }

    if (args[0] == "--i" && (argc >= 2 && argc <= 3)) {
        class Hash hash;

        std::string toHash = (argc == 2) ? "" : args[1];

        std::cout << hash.setString(toHash).make() << std::endl;

        return;
    }

    if (args[0] == "--if" && argc == 3) {
        class Hash hash;
        std::string toHash;

        this->reader.open(args[1]);
        this->reader >> toHash;

        std::cout << hash.setString(toHash).make() << std::endl;

        this->reader.close();

        return;
    }

    if (args[0] == "--g" && argc == 2) {
        this->generateFiles();

        return;
    }

    if (args[0] == "--b" && argc == 2) {
        this->performBenchmark();

        return;
    }

    if (args[0] == "--c" && argc == 2) {
//        Tester tester;
//        tester.runTests(100000, 1000, "out.txt");
        this->performCollisionTest();

        return;
    }

    if (args[0] == "--a" && argc == 2) {
        this->performAvalancheTest();

        return;
    }

    std::cout << Color::RED << "Invalid arguments were specified." << Color::RESET << std::endl << std::endl;
    this->printHelp();
}

void Application::printHelp() {
    std::cout << Color::YELLOW << "Available commands:" << Color::RESET << std::endl;

    for (const auto& command: commands) {
        std::cout << std::setfill(' ') << std::setw(4) << "";
        std::cout << std::setw(30) << std::left << Color::GREEN + command.first + Color::RESET;
        std::cout << command.second << std::endl;
    }
}

void Application::generateFiles() {
    StringGenerator generator;

    this->writer.open("files/1.txt");
    this->writer.write("a", 1);
    this->writer.close();

    this->writer.open("files/2.txt");
    this->writer.write("c", 1);
    this->writer.close();

    std::string generated = generator.setLength(1000).generate();

    this->writer.open("files/3.txt");
    this->writer.write(generated.c_str(), generated.length());
    this->writer.close();

    generated = generator.setLength(1000).generate();

    this->writer.open("files/4.txt");
    this->writer.write(generated.c_str(), generated.length());
    this->writer.close();

    generated = generator.setLength(1000).generate();
    generated[generated.length() / 2] = 'a';

    this->writer.open("files/5.txt");
    this->writer.write(generated.c_str(), generated.length());
    this->writer.close();

    generated = generator.setLength(1000).generate();
    generated[generated.length() / 2] = 'd';

    this->writer.open("files/6.txt");
    this->writer.write(generated.c_str(), generated.length());
    this->writer.close();

    std::cout << "File generation was successful!" << std::endl;
}

void Application::performBenchmark() {
    std::vector<int> lengths = { 1, 2, 4, 8, 16, 32, 64 };
    class Hash hash;
    float totalTime = 0;
    int totalSymbols = 0;

    for (int length: lengths) {
        int currentLine = 0, symbols;
        std::string lines;
        std::string line;
        std::vector<float> calculationTimes;
        std::vector<int> lineLengths;
        float time;

        this->reader.open("files/konstitucija.txt");

        while (std::getline(this->reader, line)) {
            lines.append(line);

            currentLine++;

            if (currentLine >= length) {
                Benchmark::start("hashing");

                hash.setString(lines).make();

                calculationTimes.push_back(Benchmark::end("hashing"));
                lineLengths.push_back(lines.length());

                lines.clear();

                currentLine = 0;
            }
        }

        symbols = std::accumulate(lineLengths.begin(), lineLengths.end(), 0);
        time = std::accumulate(calculationTimes.begin(), calculationTimes.end(), 0.0);

        totalSymbols += symbols;
        totalTime += time;

        std::cout << std::fixed << "Average hashing time for " << length << " lines with average of " <<
        symbols / lineLengths.size() << " symbols was "
        << time / calculationTimes.size()
        << "s" << std::endl;

        this->reader.close();
    }

    std::cout << std::endl << std::setprecision(10) << "Total hashing time for one symbol was"
    << totalTime / totalSymbols << "s" << std::endl;
}

void Application::performCollisionTest() {
    StringGenerator generator;
    class Hash hash;
    std::vector<std::pair<int, int>> lengths = { {10, 25000}, {100, 25000}, {500, 25000}, {1000, 25000} };
    int collisions = 0;

    for (auto length: lengths) {
        int symbols = length.first;
        int maxIterations = length.second;

        for (int i = 1; i <= maxIterations; i++) {
            std::string firstHash = hash.setString(generator.setLength(symbols).generate()).make();
            std::string secondHash = hash.setString(generator.setLength(symbols).generate()).make();

            if (firstHash == secondHash) {
                std::cout <<firstHash << std::endl;
                std::cout << secondHash << std::endl;
                collisions++;
            }
        }
    }

    std::cout << "Total collision count was " << collisions << std::endl;
}

void Application::performAvalancheTest() {
    StringGenerator generator;
    class Hash hash;

    double hexAverage, hexMin = 100, hexMax = 0;
    double bitAverage;
    unsigned int bitMin = 0, bitMax = 0;

    for (int i = 1; i <= 100000; i++) {
        std::string firstString = generator.setLength(1000).generate();
        std::string secondString = generator.setLength(1000).generate();

        firstString[i % 1000] = generator.setLength(1).generate()[0];
        secondString[i % 1000] = generator.setLength(1).generate()[0];

        std::string firstHash = hash.setString(firstString).make();
        std::string secondHash = hash.setString(secondString).make();

        double hexDifference = StringComparator::calculateDifference(firstHash, secondHash);
        double bitDifference = StringComparator::bitDifference(firstHash, secondHash);

        if (hexDifference < hexMin) {
            hexMin = hexDifference;
        }

        if (hexDifference > hexMax) {
            hexMax = hexDifference;
        }

        hexAverage += hexDifference;

        if (bitDifference < bitMin || i == 1) {
            bitMin = bitDifference;
        }

        if (bitDifference > bitMax) {
            bitMax = bitDifference;
        }

        bitAverage += bitDifference;
    }

    hexAverage = hexAverage / 100000;
    bitAverage = bitAverage / 100000;

    std::cout << std::setprecision(2) << "Minimum HEX difference was: " << hexMin << "%" << std::endl;
    std::cout << std::setprecision(2) << "Maximum HEX difference was: " << hexMax << "%" << std::endl;
    std::cout << std::setprecision(2) << "Average HEX difference was: " << hexAverage << "%" << std::endl;

    std::cout << std::endl;

    std::cout << std::fixed << "Minimum bit difference was: " << bitMin << "" << std::endl;
    std::cout << std::fixed << "Maximum bit difference was: " << bitMax << "" << std::endl;
    std::cout << std::fixed << "Average bit difference was: " << bitAverage << "" << std::endl;
}
