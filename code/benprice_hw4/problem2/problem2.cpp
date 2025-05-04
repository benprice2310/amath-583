// parallel_gemm.cpp
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <fstream>
#include <future>
#include "ref_dgemm.hpp"
#include "utils.hpp"

const int ntrials = 3;
const int MAX_SIZE = 200;

// Benchmark function
struct Timings
{
    int size;
    long double ijk_f, jki_f, kij_f;
    long double ijk_d, jki_d, kij_d;
};

Timings benchmark(int x)
{
    int m = x, n = x, p = x;
    double a_d = 2.0, b_d = 3.0;
    float a_f = static_cast<float>(a_d);
    float b_f = static_cast<float>(b_d);

    long double t_ijk_f = 0.0, t_jki_f = 0.0, t_kij_f = 0.0;
    long double t_ijk_d = 0.0, t_jki_d = 0.0, t_kij_d = 0.0;

    for (int t = 0; t < ntrials; ++t)
    {
        auto A_d = generateRandomMatrix<double>(m, p, -9.0, 9.0);
        auto B_d = generateRandomMatrix<double>(p, n, -9.0, 9.0);
        auto C_d = generateRandomMatrix<double>(m, n, -9.0, 9.0);

        std::vector<float> A_f(A_d.size()), B_f(B_d.size()), C_f(C_d.size());
        std::transform(A_d.begin(), A_d.end(), A_f.begin(), [](double val)
                       { return static_cast<float>(val); });
        std::transform(B_d.begin(), B_d.end(), B_f.begin(), [](double val)
                       { return static_cast<float>(val); });
        std::transform(C_d.begin(), C_d.end(), C_f.begin(), [](double val)
                       { return static_cast<float>(val); });

        std::vector<float> Cf1 = C_f, Cf2 = C_f, Cf3 = C_f;
        std::vector<double> Cd1 = C_d, Cd2 = C_d, Cd3 = C_d;

        // float ijk
        auto t1 = std::chrono::high_resolution_clock::now();
        mm_ijk(a_f, A_f, B_f, b_f, Cf1, m, p, n);
        auto t2 = std::chrono::high_resolution_clock::now();
        t_ijk_f += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();

        // float jki
        t1 = std::chrono::high_resolution_clock::now();
        mm_jki(a_f, A_f, B_f, b_f, Cf2, m, p, n);
        t2 = std::chrono::high_resolution_clock::now();
        t_jki_f += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();

        // float kij
        t1 = std::chrono::high_resolution_clock::now();
        mm_kij(a_f, A_f, B_f, b_f, Cf3, m, p, n);
        t2 = std::chrono::high_resolution_clock::now();
        t_kij_f += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();

        // double ijk
        t1 = std::chrono::high_resolution_clock::now();
        mm_ijk(a_d, A_d, B_d, b_d, Cd1, m, p, n);
        t2 = std::chrono::high_resolution_clock::now();
        t_ijk_d += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();

        // double jki
        t1 = std::chrono::high_resolution_clock::now();
        mm_jki(a_d, A_d, B_d, b_d, Cd2, m, p, n);
        t2 = std::chrono::high_resolution_clock::now();
        t_jki_d += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();

        // double kij
        t1 = std::chrono::high_resolution_clock::now();
        mm_kij(a_d, A_d, B_d, b_d, Cd3, m, p, n);
        t2 = std::chrono::high_resolution_clock::now();
        t_kij_d += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
    }

    return Timings{
        x,
        t_ijk_f / ntrials, t_jki_f / ntrials, t_kij_f / ntrials,
        t_ijk_d / ntrials, t_jki_d / ntrials, t_kij_d / ntrials};
}

int main()
{
    printSectionTitle("BEGIN PROBLEM 2 (Parallel)");

    std::ofstream out("timing_results_parallel.csv");
    out << "size,ijk_float,jki_float,kij_float,ijk_double,jki_double,kij_double\n";

    std::vector<std::future<Timings>> futures;

    for (int size = 2; size <= MAX_SIZE; ++size)
    {
        futures.emplace_back(std::async(std::launch::async, benchmark, size));
    }

    for (auto &f : futures)
    {
        Timings t = f.get();
        out << t.size << ","
            << t.ijk_f << "," << t.jki_f << "," << t.kij_f << ","
            << t.ijk_d << "," << t.jki_d << "," << t.kij_d << "\n";
    }

    out.close();
    printSectionTitle("END PROBLEM 2 (Parallel)");
    return 0;
}