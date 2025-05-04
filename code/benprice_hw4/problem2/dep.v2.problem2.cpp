// problem2.cpp
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>
#include "ref_dgemm.hpp"
#include "utils.hpp"

const int PRINT_WIDTH = 6;
const bool PRINT_TIMES = true;
const bool PRINT_MATRICES = false;

void demoSingleMatrixCase()
{
    std::cout << "\n"
              << std::string(80, '-');
    int m = 5;
    int n = 3;
    int p = 4;

    int a = 7;
    int b = 8;

    // 2D vectors for testing
    std::vector<std::vector<int>> A_2D{
        {-4, -5, 1, -4},
        {-4, -1, -2, -4},
        {-1, 0, -1, -1},
        {4, -1, -5, -3},
        {3, 2, 5, 0}};
    std::vector<std::vector<int>> B_2D{
        {-2, 3, 5},
        {-5, 3, -1},
        {5, -1, 5},
        {-5, 1, -2}};
    std::vector<std::vector<int>> C_2D{
        {2, -4, 1},
        {2, -4, 4},
        {0, 5, 2},
        {2, -4, -3},
        {2, -5, -1}};

    // Column major vectors for testing
    std::vector<int> A_cm{-4, -4, -1, 4, 3, -5, -1, 0, -1, 2, 1, -2, -1, -5, 5, -4, -4, -1, -3, 0};
    std::vector<int> B_cm{-2, 5, 5, -5, 3, -3, -1, 1, 5, -1, 5, -2};
    std::vector<int> C_cm_REF{2, 2, 0, 2, 2, -4, -4, 5, -4, -5, 1, 4, 2, -3, -1};
    std::vector<int> C_cm = C_cm_REF;

    std::cout << "\n=== Sizes ===\n";
    std::cout << "size A: [m, p] = [" << A_2D.size() << ", " << A_2D[0].size() << "]\n";
    std::cout << "size B: [p, n] = [" << B_2D.size() << ", " << B_2D[0].size() << "]\n";
    std::cout << "size C: [m, n] = [" << C_2D.size() << ", " << C_2D[0].size() << "]\n\n";

    // printSectionHeader("A 2D Matrix");
    // print2DVector(A_2D);
    printSectionTitle("Demo Single Matrix Case");
    printSubheaderLeft("A Column Major Flattend Matrix");
    printColumnMajorVectorMatrix(A_cm, m, p);
    printSubheaderLeft("B Column Major Flattend Matrix");
    printColumnMajorVectorMatrix(B_cm, p, n);
    printSubheaderLeft("C Column Major Flattend Matrix");
    printColumnMajorVectorMatrix(C_cm, m, n);
    printSubheaderLeft("Other properties");
    std::cout << "a = " << a << "\n";
    std::cout << "b = " << b << "\n";
    std::cout << "m = " << m << "\n";
    std::cout << "n = " << n << "\n";
    std::cout << "p = " << p << "\n";

    // Apply {ijk} calculations
    printHeader("Apply mm_ijk: C = a*A*B + b*C");
    mm_ijk(a, A_cm, B_cm, b, C_cm, m, p, n);
    printSubheaderLeft("Adjusted C Matrix");
    printColumnMajorVectorMatrix(C_cm, m, n);

    // Apply {jki} calculations
    C_cm = C_cm_REF;
    printHeader("Apply mm_jki: C = a*A*B + b*C");
    mm_jki(a, A_cm, B_cm, b, C_cm, m, p, n);
    printSubheaderLeft("Adjusted C Matrix");
    printColumnMajorVectorMatrix(C_cm, m, n);

    // Apply {kij} calculations
    C_cm = C_cm_REF;
    printHeader("Apply mm_kij: C = a*A*B + b*C");
    mm_kij(a, A_cm, B_cm, b, C_cm, m, p, n);
    printSubheaderLeft("Adjusted C Matrix");
    printColumnMajorVectorMatrix(C_cm, m, n);

    std::cout << std::string(80, '-') << "\n";
}

int main()
{
    // START OF PROGRAM
    std::cout << "\n";
    printSectionTitle("BEGIN PROBLEM 2");
    std::cout << "\n";

    std::ofstream csv("timing_results.csv");
    csv << "size,ijk_float,jki_float,kij_float,ijk_double,jki_double,kij_double\n";

    // demoSingleMatrixCase();
    // declare some stuff
    int m;
    int n;
    int p;
    float a_float;
    float b_float;
    std::vector<float> A_float;
    std::vector<float> B_float;
    std::vector<float> C_float;
    double a_double;
    double b_double;
    std::vector<double> A_double;
    std::vector<double> B_double;
    std::vector<double> C_double;

    // total trial timer
    auto start_trial = std::chrono::high_resolution_clock::now();
    auto stop_trial = std::chrono::high_resolution_clock::now();

    // permutation {ijk} timers
    auto start_ijk_float = std::chrono::high_resolution_clock::now();
    auto stop_ijk_float = std::chrono::high_resolution_clock::now();

    auto start_ijk_double = std::chrono::high_resolution_clock::now();
    auto stop_ijk_double = std::chrono::high_resolution_clock::now();

    // permutation {jki} timers
    auto start_jki_float = std::chrono::high_resolution_clock::now();
    auto stop_jki_float = std::chrono::high_resolution_clock::now();

    auto start_jki_double = std::chrono::high_resolution_clock::now();
    auto stop_jki_double = std::chrono::high_resolution_clock::now();

    // permutation {kij} timers
    auto start_kij_float = std::chrono::high_resolution_clock::now();
    auto stop_kij_float = std::chrono::high_resolution_clock::now();

    auto start_kij_double = std::chrono::high_resolution_clock::now();
    auto stop_kij_double = std::chrono::high_resolution_clock::now();

    // duration variables
    auto duration_ijk_float = std::chrono::duration_cast<std::chrono::nanoseconds>(stop_ijk_float - start_ijk_float);
    auto duration_ijk_double = std::chrono::duration_cast<std::chrono::nanoseconds>(stop_ijk_double - start_ijk_double);

    auto duration_jki_float = std::chrono::duration_cast<std::chrono::nanoseconds>(stop_jki_float - start_jki_float);
    auto duration_jki_double = std::chrono::duration_cast<std::chrono::nanoseconds>(stop_jki_double - start_jki_double);

    auto duration_kij_float = std::chrono::duration_cast<std::chrono::nanoseconds>(stop_kij_float - start_kij_float);
    auto duration_kij_double = std::chrono::duration_cast<std::chrono::nanoseconds>(stop_kij_double - start_kij_double);

    // total duration
    auto duration_trial = std::chrono::duration_cast<std::chrono::nanoseconds>(stop_trial - start_trial);

    // elapsed time variables
    long double elapsed_time_trial = 0.L;
    long double elapsed_time_ijk_float = 0.L;
    long double elapsed_time_ijk_double = 0.L;
    long double elapsed_time_jki_float = 0.L;
    long double elapsed_time_jki_double = 0.L;
    long double elapsed_time_kij_float = 0.L;
    long double elapsed_time_kij_double = 0.L;

    // average time variables
    long double avg_time_trial;
    long double avg_time_ijk_float;
    long double avg_time_ijk_double;
    long double avg_time_jki_float;
    long double avg_time_jki_double;
    long double avg_time_kij_float;
    long double avg_time_kij_double;

    const int ntrials = 3;

    for (int x = 2; x < 513; ++x)
    {
        printSectionTitle("Matrix size " + std::to_string(x) + " x " + std::to_string(x));
        for (int t = 0; t < ntrials; ++t)
        {
            printSubheaderLeft("Trial " + std::to_string(t + 1) + " of " + std::to_string(ntrials) + " (m,n,p = " + std::to_string(x) + ")");
            start_trial = std::chrono::high_resolution_clock::now();

            // define parameters
            m = x;
            n = x;
            p = x;
            a_double = 2.0;
            b_double = 3.0;

            // generate random matrices
            A_double = generateRandomMatrix<double>(m, p, -9.0, 9.0);
            B_double = generateRandomMatrix<double>(p, n, -9.0, 9.0);
            C_double = generateRandomMatrix<double>(m, n, -9.0, 9.0);

            // convert double to float
            a_float = static_cast<float>(a_double);
            b_float = static_cast<float>(b_double);
            std::vector<float> A_float(A_double.size());
            std::transform(A_double.begin(), A_double.end(), A_float.begin(),
                           [](double d)
                           { return static_cast<float>(d); });
            std::vector<float> B_float(B_double.size());
            std::transform(B_double.begin(), B_double.end(), B_float.begin(),
                           [](double d)
                           { return static_cast<float>(d); });
            std::vector<float> C_float(C_double.size());
            std::transform(C_double.begin(), C_double.end(), C_float.begin(),
                           [](double d)
                           { return static_cast<float>(d); });

            // Allocate C matrix copies
            std::vector<float> Cf1 = C_float;
            std::vector<float> Cf2 = C_float;
            std::vector<float> Cf3 = C_float;
            std::vector<double> Cd1 = C_double;
            std::vector<double> Cd2 = C_double;
            std::vector<double> Cd3 = C_double;

            // some printing
            if (x < 5 || PRINT_MATRICES)
            {
                printSubheaderLeft("A Row Major Flattend Matrix");
                printRowMajorVectorMatrix(A_float, m, p);
                printSubheaderLeft("B Row Major Flattend Matrix");
                printRowMajorVectorMatrix(B_float, p, n);
                printSubheaderLeft("C Row Major Flattend Matrix");
                printRowMajorVectorMatrix(C_float, m, n);
            }

            // perform float calculations
            start_ijk_float = std::chrono::high_resolution_clock::now();
            mm_ijk(a_float, A_float, B_float, b_float, Cf1, m, p, n);
            stop_ijk_float = std::chrono::high_resolution_clock::now();

            start_jki_float = std::chrono::high_resolution_clock::now();
            mm_jki(a_float, A_float, B_float, b_float, Cf2, m, p, n);
            stop_jki_float = std::chrono::high_resolution_clock::now();

            start_kij_float = std::chrono::high_resolution_clock::now();
            mm_kij(a_float, A_float, B_float, b_float, Cf3, m, p, n);
            stop_kij_float = std::chrono::high_resolution_clock::now();

            // perform double calculations
            start_ijk_double = std::chrono::high_resolution_clock::now();
            mm_ijk(a_double, A_double, B_double, b_double, Cd1, m, p, n);
            stop_ijk_double = std::chrono::high_resolution_clock::now();

            start_jki_double = std::chrono::high_resolution_clock::now();
            mm_jki(a_double, A_double, B_double, b_double, Cd2, m, p, n);
            stop_jki_double = std::chrono::high_resolution_clock::now();

            start_kij_double = std::chrono::high_resolution_clock::now();
            mm_kij(a_double, A_double, B_double, b_double, Cd3, m, p, n);
            stop_kij_double = std::chrono::high_resolution_clock::now();

            // end do work
            stop_trial = std::chrono::high_resolution_clock::now();

            // calculate durations
            duration_trial = std::chrono::duration_cast<std::chrono::nanoseconds>(stop_trial - start_trial);

            duration_ijk_float = std::chrono::duration_cast<std::chrono::nanoseconds>(stop_ijk_float - start_ijk_float);
            duration_jki_float = std::chrono::duration_cast<std::chrono::nanoseconds>(stop_jki_float - start_jki_float);
            duration_kij_float = std::chrono::duration_cast<std::chrono::nanoseconds>(stop_kij_float - start_kij_float);

            duration_ijk_double = std::chrono::duration_cast<std::chrono::nanoseconds>(stop_ijk_double - start_ijk_double);
            duration_jki_double = std::chrono::duration_cast<std::chrono::nanoseconds>(stop_jki_double - start_jki_double);
            duration_kij_double = std::chrono::duration_cast<std::chrono::nanoseconds>(stop_kij_double - start_kij_double);

            // calculate elapsed times
            elapsed_time_trial += duration_trial.count();
            elapsed_time_ijk_float += duration_ijk_float.count();
            elapsed_time_ijk_double += duration_ijk_double.count();
            elapsed_time_jki_float += duration_jki_float.count();
            elapsed_time_jki_double += duration_jki_double.count();
            elapsed_time_kij_float += duration_kij_float.count();
            elapsed_time_kij_double += duration_kij_double.count();

            std::cout << "Elapsed time: " << duration_trial.count() / 1e9 << " seconds\n";
        }
        // calculate average times
        avg_time_trial = elapsed_time_trial / ntrials;

        avg_time_jki_float = elapsed_time_jki_float / ntrials;
        avg_time_ijk_float = elapsed_time_ijk_float / ntrials;
        avg_time_kij_float = elapsed_time_kij_float / ntrials;

        avg_time_ijk_double = elapsed_time_ijk_double / ntrials;
        avg_time_jki_double = elapsed_time_jki_double / ntrials;
        avg_time_kij_double = elapsed_time_kij_double / ntrials;

        // save or report findings
        // printSubheaderLeft("Average time for " + std::to_string(ntrials) + " trials" + " (size = " + std::to_string(x) + ") " + std::to_string(avg_time) + " ns");

        // print results
        if (PRINT_TIMES)
        {
            printHeader("<float> Avg Time (ntrials = " + std::to_string(ntrials) + ", size = " + std::to_string(x) + ")");
            std::cout << "\nt_avg_float for " << ntrials << " trials (ijk): " << avg_time_ijk_float << " ns\n";
            std::cout << "t_avg_float for " << ntrials << " trials (jki): " << avg_time_jki_float << " ns\n";
            std::cout << "t_avg_float for " << ntrials << " trials (kij): " << avg_time_kij_float << " ns\n";

            printHeader("<double> Avg Time (ntrials = " + std::to_string(ntrials) + ", size = " + std::to_string(x) + ")");
            std::cout << "\nt_avg_double for " << ntrials << " trials (ijk): " << avg_time_ijk_double << " ns\n";
            std::cout << "t_avg_double for " << ntrials << " trials (jki): " << avg_time_jki_double << " ns\n";
            std::cout << "t_avg_double for " << ntrials << " trials (kij): " << avg_time_kij_double << " ns\n";

            printHeader("Total Avg Time (ntrials = " + std::to_string(ntrials) + ", size = " + std::to_string(x) + ")");
            std::cout << "\nt_avg for " << ntrials << " trials (x = " << x << "): " << avg_time_trial << " ns\n";
        }

        // save results to csv
        csv << x << ","
            << avg_time_ijk_float << ","
            << avg_time_jki_float << ","
            << avg_time_kij_float << ","
            << avg_time_ijk_double << ","
            << avg_time_jki_double << ","
            << avg_time_kij_double << "\n";

        // zero time again
        elapsed_time_trial = 0.L;
        elapsed_time_ijk_float = 0.L;
        elapsed_time_ijk_double = 0.L;
        elapsed_time_jki_float = 0.L;
        elapsed_time_jki_double = 0.L;
        elapsed_time_kij_float = 0.L;
        elapsed_time_kij_double = 0.L;
    }

    // END OF PROGRAM
    printSectionTitle("END PROBLEM 2");
    std::cout << "\n";
    csv.close();
    return 0;
}