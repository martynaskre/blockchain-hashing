//
// Created by Martynas Skrebė on 2022-09-23.
//

#ifndef BLOCKCHAIN_BENCHMARK_H
#define BLOCKCHAIN_BENCHMARK_H


#include <chrono>
#include <map>
#include <string>


struct BenchmarkResult {
    std::chrono::steady_clock::time_point start;
    std::string title;
};

class Benchmark {
    static std::map<std::string, BenchmarkResult> benchmarks;

public:
    static void start(const std::string& benchmark);
    static float end(const std::string& benchmark);
};


#endif //BLOCKCHAIN_BENCHMARK_H
