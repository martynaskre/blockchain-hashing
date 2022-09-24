//
// Created by Martynas Skrebė on 2022-09-23.
//

#include "Benchmark.h"

std::map<std::string, BenchmarkResult> Benchmark::benchmarks;

void Benchmark::start(const std::string& benchmark) {
    auto existingBenchmark = Benchmark::benchmarks.find(benchmark);

    if (existingBenchmark != Benchmark::benchmarks.end()) {
        existingBenchmark->second.start = std::chrono::steady_clock::now();
    } else {
        BenchmarkResult result = { std::chrono::steady_clock::now() };

        Benchmark::benchmarks.insert(std::make_pair(benchmark, result));
    }
}

float Benchmark::end(const std::string& benchmark) {
    auto existingBenchmark = Benchmark::benchmarks.find(benchmark);

    if (existingBenchmark != Benchmark::benchmarks.end()) {
        std::chrono::steady_clock::time_point timeEnd = std::chrono::steady_clock::now();

        Benchmark::benchmarks.erase(existingBenchmark);

        return std::chrono::duration<float> (timeEnd - existingBenchmark->second.start).count();
    }

    return 0;
}