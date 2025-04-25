#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <random>
#include <iomanip>
#include <string>
#include "ref_dgemv.hpp"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " output_csv_path\n";
        return 1;
    }

    const std::string output_csv = argv[1];
    const int ntrial = 3;

    std::ofstream fout(output_csv);
    fout << "n,FLOPs_per_sec\n";
    fout << std::scientific << std::setprecision(8);

    std::mt19937 gen(42);
    std::uniform_real_distribution<double> dist(0.1, 2.0);

    for (int n = 2; n <= 512; ++n) {
        int m = n; // For performance tests, use square matrices
        std::vector<std::vector<double>> A(m, std::vector<double>(n));
        std::vector<double> x(n), y(m);

        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                A[i][j] = dist(gen);

        for (int i = 0; i < n; ++i)
            x[i] = dist(gen);

        for (int i = 0; i < m; ++i)
            y[i] = dist(gen);

        double alpha = dist(gen);
        double beta = dist(gen);

        long double elapsed_time = 0.L;
        for (int t = 0; t < ntrial; ++t) {
            auto y_copy = y;
            auto start = std::chrono::high_resolution_clock::now();
            dgemv(alpha, A, x, beta, y_copy);
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
            elapsed_time += duration.count() * 1.e-9;
        }

        double avg_time = elapsed_time / ntrial;
        double flops = (2.0 * m * n) / avg_time;

        fout << n << "," << flops << "\n";
        fout.flush();
        std::cout << "n=" << n << ", MFLOPs/sec=" << flops / 1e6 << std::endl;
    }

    fout.close();
    std::cout << "\nData written to " << output_csv << "\n";
    return 0;
}