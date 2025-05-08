// strassen_test.cpp
#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>
#include <iomanip>
#include <cstdlib>
#include <future>
#include <tuple>
#include <algorithm>

using std::cerr;
using std::cout;
using std::endl;
using std::make_tuple;
using std::tuple;
using std::vector;

// Forward-declare your routines (instantiated for double in strassen.cpp)
template <typename T>
vector<vector<T>> addMatrix(const vector<vector<T>> &A,
                            const vector<vector<T>> &B);
template <typename T>
vector<vector<T>> subtractMatrix(const vector<vector<T>> &A,
                                 const vector<vector<T>> &B);
template <typename T>
vector<vector<T>> strassenMultiply(const vector<vector<T>> &A,
                                   const vector<vector<T>> &B);

// Worker: does one n, returns (n, avg_ms, gflops)
tuple<int, double, double> run_size(int n, int ntrial = 3)
{
    // Progress: print to stderr
    cerr << "Starting n=" << n << " on thread.\n";

    // Build random matrices
    vector<vector<double>> A(n, vector<double>(n));
    vector<vector<double>> B(n, vector<double>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            A[i][j] = std::rand() / double(RAND_MAX),
            B[i][j] = std::rand() / double(RAND_MAX);

    // Warm-up
    auto C0 = strassenMultiply<double>(A, B);

    // Time trials
    double sum_ms = 0;
    for (int t = 0; t < ntrial; ++t)
    {
        auto t0 = std::chrono::high_resolution_clock::now();
        auto C = strassenMultiply<double>(A, B);
        auto t1 = std::chrono::high_resolution_clock::now();
        sum_ms += std::chrono::duration<double, std::milli>(t1 - t0).count();
    }
    double avg_ms = sum_ms / ntrial;

    // Compute effective GFLOP/s (≈ n^{log2(7)})
    double ops = std::pow(n, std::log2(7.0));
    double gflops = (ops / (avg_ms / 1000.0)) / 1e9;

    return make_tuple(n, avg_ms, gflops);
}

int main()
{
    // list of sizes 2,4,8,...,512
    vector<int> sizes;
    for (int n = 2; n <= 512; n *= 2)
        sizes.push_back(n);

    // launch async tasks
    vector<std::future<tuple<int, double, double>>> futures;
    futures.reserve(sizes.size());
    for (int n : sizes)
    {
        futures.push_back(
            std::async(std::launch::async, run_size, n, 3));
    }

    // collect results
    vector<tuple<int, double, double>> results;
    results.reserve(sizes.size());
    for (auto &f : futures)
    {
        results.push_back(f.get());
    }

    // sort by n
    std::sort(results.begin(), results.end(),
              [](auto &a, auto &b)
              { return std::get<0>(a) < std::get<0>(b); });

    // print CSV header
    cout << "n,avg_time_ms,gflops\n";
    // print lines
    for (auto &t : results)
    {
        int n = std::get<0>(t);
        double avg_ms = std::get<1>(t);
        double gfl = std::get<2>(t);
        cout << n << ","
             << std::fixed << std::setprecision(2) << avg_ms << ","
             << std::fixed << std::setprecision(2) << gfl << "\n";
    }
    return 0;
}