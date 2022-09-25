//
// Created by Martynas Skrebė on 2022-09-20.
//

#include "Application.h"
#include <iostream>
#include <sstream>
#include "Benchmark.h"
#include "StringComparator.h"
#include "Color.h"

const std::vector<std::pair<std::string, std::string>> Application::commands = {
        {"--help", "Shows available commands"},
        {"--i {string}", "Hashes provided string"},
        {"--if {file_path}", "Hashes provided file contents"},
        {"--g", "Generates test files"},
        {"--b {file_path?}", "Runs hashing benchmark for constitution.txt file. If path is not provided, then it will look for a file with path \"files/constitution.txt\""},
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
        std::string input = (argc == 2) ? "" : args[1];

        this->hashInput(input);

        return;
    }

    if (args[0] == "--if" && argc == 3) {
        this->hashFile(args[1]);

        return;
    }

    if (args[0] == "--g" && argc == 2) {
        this->generateFiles();

        return;
    }

    if (args[0] == "--b" && (argc >= 2 && argc <= 3)) {
        std::string filename = (argc == 2) ? "files/constitution.txt" : args[1];

        this->performBenchmark(filename);

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

void Application::hashInput(const std::string &input) {
    std::cout << hash.setString(input).make() << std::endl;
}

void Application::hashFile(const std::string &filename) {
    this->reader.open(filename);

    if (this->reader.fail()) {
        std::cout << Color::RED << "An error occurred while opening file. Check if file exists." << Color::RESET << std::endl;

        return;
    }

    std::stringstream fileBuffer;
    fileBuffer << this->reader.rdbuf();

    std::cout << hash.setString(fileBuffer.str()).make() << std::endl;

    this->reader.close();
}

void Application::generateFiles() {
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

void Application::performBenchmark(const std::string &filename) {
    std::cout << Color::YELLOW << "Starting performance benchmark..." << Color::RESET << std::endl << std::endl;

    this->reader.open(filename);

    if (this->reader.fail()) {
        std::cout << Color::RED << "An error occurred while opening file. Check if file exists." << Color::RESET << std::endl;

        return;
    }

    std::vector<int> lengths = { 1, 2, 4, 8, 16, 32, 64 };
    float totalTime = 0;
    int totalSymbols = 0;

    for (int length: lengths) {
        int currentLine = 0, symbols;
        std::string lines;
        std::string line;
        std::vector<float> calculationTimes;
        std::vector<int> lineLengths;
        float time;

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

        std::cout << std::fixed << "Average hashing time for " << Color::CYAN << length << Color::RESET << " lines with average of " <<
        Color::CYAN << symbols / lineLengths.size() << Color::RESET << " symbols was "
        << Color::MAGENTA << time / calculationTimes.size()
        << "s" << Color::RESET << std::endl;

        this->reader.clear();
        this->reader.seekg(0, std::ios::beg);
    }

    this->reader.close();
}

void Application::performCollisionTest() {
    std::cout << Color::YELLOW << "Starting collision test..." << Color::RESET << std::endl << std::endl;

    std::vector<std::pair<int, int>> lengths = { {10, 25000}, {100, 25000}, {500, 25000}, {1000, 25000} };
    int collisions = 0;

    for (auto length: lengths) {
        int symbols = length.first;
        int maxIterations = length.second;

        for (int i = 1; i <= maxIterations; i++) {
            std::string firstHash = hash.setString(generator.setLength(symbols).generate()).make();
            std::string secondHash = hash.setString(generator.setLength(symbols).generate()).make();

            if (firstHash == secondHash) {
                collisions++;
            }
        }
    }

    std::cout << "Total collision count was " << Color::MAGENTA << collisions << Color::RESET << std::endl;
}

void Application::performAvalancheTest() {
    std::cout << Color::YELLOW << "Starting avalanche test..." << Color::RESET << std::endl << std::endl;

    double hexAverage = 0, hexMin = 100, hexMax = 0;
    double bitAverage = 0;
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

    std::cout << std::setprecision(4) << "Minimum HEX difference was: " << Color::MAGENTA << hexMin << "%" << Color::RESET << std::endl;
    std::cout << std::setprecision(4) << "Maximum HEX difference was: " << Color::MAGENTA << hexMax << "%" << Color::RESET << std::endl;
    std::cout << std::setprecision(4) << "Average HEX difference was: " << Color::MAGENTA << hexAverage << "%" << Color::RESET << std::endl;

    std::cout << std::endl;

    std::cout << std::fixed << "Minimum bit difference was: " << Color::MAGENTA << bitMin << Color::RESET << std::endl;
    std::cout << std::fixed << "Maximum bit difference was: " << Color::MAGENTA << bitMax << Color::RESET << std::endl;
    std::cout << std::fixed << "Average bit difference was: " << Color::MAGENTA << bitAverage << Color::RESET << std::endl;
}
