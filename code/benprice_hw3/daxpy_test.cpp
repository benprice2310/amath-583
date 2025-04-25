#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <random>
#include <iomanip>
#include <string>
#include "ref_daxpy.hpp"

void printSeparator(const std::string &msg)
{
    std::cout << "\n=== " << msg << " ===\n\n";
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " output_csv_path>\n";
        return 1;
    }

    printSeparator("DAXPY Performance Test");

    // set up parameters
    const int ntrials = 3;
    const int size_min = 2;
    const int size_max = 512;

    // set up random number generator
    std::mt19937 gen(42);                                    // Seed with a fixed value for reproducibility
    std::uniform_real_distribution<double> dist(0.1, 2.0);   // Uniform distribution between 0.1 and 2.0
    std::uniform_real_distribution<double> dist2(-1.0, 1.0); // Uniform distribution between -1.0 and 1.0

    // set up timing variables
    long double elapsed_time = 0.L;
    long double avg_time;
    long double flops;

    // Write to a file
    std::string output_csv = argv[1];
    std::ofstream fout(output_csv);
    fout << "n,FLOPs_per_sec\n";
    fout << std::setprecision(8) << std::scientific;

    // loop on problem size
    for (int n = size_min; n <= size_max; n++)
    {
        // define vector sizes
        std::vector<double> x(n), y(n);
        double alpha = dist(gen);

        // initialize vectors with random values
        for (int i = 0; i < n; ++i)
        {
            x[i] = dist(gen);
            y[i] = dist(gen);
        }

        // perform an experiment
        for (int t = 0; t < ntrials; t++)
        {
            auto y_copy = y; // Copy y to preserve original values

            // set up timer
            auto start = std::chrono::high_resolution_clock::now();

            // do work(size i, trial t)
            daxpy(alpha, x, y_copy);

            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);

            elapsed_time += duration.count() * 1.e-9; // Convert to seconds
        }

        avg_time = elapsed_time / static_cast<long double>(ntrials);
        flops = (2.L * static_cast<long double>(n)) / avg_time; // 2*n flops for daxpy

        /* // console output
        std::cout << "size " << n << "\n";
        std::cout << "Final elapsed time: " << elapsed_time << " s\n";
        std::cout << "Average time: " << avg_time << " s\n";
        std::cout << "FLOPS: " << flops << "\n\n"; */

        // write to file
        fout << n << "," << flops << '\n';
        fout.flush();

        std::cout << "n=" << n << ", MFLOPs/sec=" << flops / 1e6 << std::endl;

        // zero time again
        elapsed_time = 0.L;
    }

    fout.close();

    std::cout << "\nData written to build/daxpy_performance.csv\n";

    printSeparator("End of program");

    return 0;
}