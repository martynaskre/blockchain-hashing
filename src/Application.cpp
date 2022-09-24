//
// Created by Martynas Skrebė on 2022-09-20.
//

#include "Application.h"
#include "iostream"
#include "Hash.h"
#include "StringGenerator.h"
#include "Benchmark.h"

void Application::run(int argc, char *argv[]) {
    std::vector<std::string> args(argv + 1, argv + argc);

    if (args[0] == "--i") {
        class Hash hash;

        std::cout << hash.setString(args[1]).make() << std::endl;

        return;
    }

    if (args[0] == "--if") {
        class Hash hash;
        std::string toHash;

        this->reader.open(args[1]);
        this->reader >> toHash;

        std::cout << hash.setString(toHash).make() << std::endl;

        this->reader.close();

        return;
    }

    if (args[0] == "--g") {
        this->generateFiles();

        return;
    }

    if (args[0] == "--b") {
        this->performBenchmark();

        return;
    }

    if (args[0] == "--c") {
        this->performCollisionTest();

        return;
    }

    std::cout << "No operation was selected." << std::endl;
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
                collisions++;
            }
        }
    }

    std::cout << "Total collisions count was " << collisions << std::endl;
}
