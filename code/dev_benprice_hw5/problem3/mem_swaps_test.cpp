#include "mem_swaps.hpp"
#include <chrono>
#include <iostream>
#include <vector>
#include <iomanip>

int main()
{
    std::srand(0);

    std::vector<int> sizes;
    for (int m = 16; m <= 4096; m *= 2)
        sizes.push_back(m);

    const int ntrial = 5;
    std::cout << "N,avg_row_swap (μs),avg_col_swap (μs)\n";

    for (int N : sizes)
    {
        // build an N×N matrix
        std::vector<double> A(N * N);
        for (auto &v : A)
            v = std::rand() / double(RAND_MAX);

        // time row swaps
        double sum_row = 0;
        for (int t = 0; t < ntrial; ++t)
        {
            // C++14: no structured bindings
            std::pair<int, int> rowIndices = getRandomIndices(N);
            int i = rowIndices.first;
            int j = rowIndices.second;

            auto B = A; // copy fresh
            auto t0 = std::chrono::high_resolution_clock::now();
            swapRows(B, N, N, i, j);
            auto t1 = std::chrono::high_resolution_clock::now();
            sum_row += std::chrono::duration<double, std::micro>(t1 - t0).count();
        }

        // time col swaps
        double sum_col = 0;
        for (int t = 0; t < ntrial; ++t)
        {
            std::pair<int, int> colIndices = getRandomIndices(N);
            int i = colIndices.first;
            int j = colIndices.second;

            auto B = A;
            auto t0 = std::chrono::high_resolution_clock::now();
            swapCols(B, N, N, i, j);
            auto t1 = std::chrono::high_resolution_clock::now();
            sum_col += std::chrono::duration<double, std::micro>(t1 - t0).count();
        }

        std::cout << N << ","
                  << std::fixed << std::setprecision(2)
                  << (sum_row / ntrial) << ","
                  << (sum_col / ntrial) << "\n";
    }
    return 0;
}