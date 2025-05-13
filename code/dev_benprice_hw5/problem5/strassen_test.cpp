#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>
#include <iomanip>
#include <cstdlib>

using std::cout;
using std::endl;
using std::vector;

// Forward-declare the templated routines (they’re instantiated for double
// inside strassen.cpp via your explicit template instantiations).
template <typename T>
vector<vector<T>> addMatrix(const vector<vector<T>> &A,
                            const vector<vector<T>> &B);

template <typename T>
vector<vector<T>> subtractMatrix(const vector<vector<T>> &A,
                                 const vector<vector<T>> &B);

template <typename T>
vector<vector<T>> strassenMultiply(const vector<vector<T>> &A,
                                   const vector<vector<T>> &B);

int main()
{
    const int ntrial = 3;
    cout << "n,avg_time_ms,gflops\n";

    for (int n = 2; n <= 512; n += 2)
    {
        std::cerr << "Testing n=" << n << "..." << std::endl;
        // Build random A, B
        vector<vector<double>> A(n, vector<double>(n));
        vector<vector<double>> B(n, vector<double>(n));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                A[i][j] = std::rand() / double(RAND_MAX),
                B[i][j] = std::rand() / double(RAND_MAX);

        // Warm‐up call (to avoid one‐time costs skewing the first trial)
        auto C0 = strassenMultiply<double>(A, B);

        // Time ntrial runs
        double sum_ms = 0;
        for (int t = 0; t < ntrial; ++t)
        {
            auto t0 = std::chrono::high_resolution_clock::now();
            auto C = strassenMultiply<double>(A, B);
            auto t1 = std::chrono::high_resolution_clock::now();
            sum_ms += std::chrono::duration<double, std::milli>(t1 - t0).count();
        }

        double avg_ms = sum_ms / ntrial;
        // Approximate flop count ~ n^{log2(7)}
        double ops = std::pow(n, std::log2(7.0));
        double gflops = (ops / (avg_ms / 1000.0)) / 1e9;

        cout << n << ","
             << std::fixed << std::setprecision(2) << avg_ms << ","
             << std::fixed << std::setprecision(2) << gflops << "\n";
    }

    return 0;
}