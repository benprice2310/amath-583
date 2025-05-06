// problem6.cpp

#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <chrono>
#include "file_swaps.hpp"
#include "matrix_class.hpp"
#include "utils.hpp"

int main(int argc, char *argv[])
{
    std::cout << "\n=== Problem 6 : File Access Time ===\n ";

    // Parameters
    const int numRows = 1024;
    const int numCols = 1024;
    const std::string filename = "matrix_data.bin";

    // Seed random
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Construct matrix A with more interesting data
    Matrix<double>
        A({{1.0, 2.0},
           {-4.0, 0.0},
           {3.14, -2.71}});

    Matrix<double> At = A.transpose();

    std::cout << "\nMatrix A:\n";
    A.print(12);
    std::cout << "\n";

    std::cout << "\nMatrix A.T:\n";
    At.print(12);
    std::cout << "\n\n";

    std::cout << "A  rows, cols: " << A.rows() << ", " << A.cols() << "\n";
    std::cout << "At rows, cols: " << At.rows() << ", " << At.cols() << "\n\n";

    const std::vector<double> dataA = A.data();
    const std::vector<double> dataAtranspose = At.data();

    // std::cout << "A data: " << std::to_string(dataA) << "\n";

    std::cout << "A matrix:    ";
    printVector(dataA);
    std::cout << "A transpose: ";
    printVector(dataAtranspose);
    std::cout << "\n";

    int i = 2;
    int j = 0;
    // // Row-major
    // data[i * ncols + j] = A(i, j);  // Correct for row-major
    // A(2,0) should give 3.14
    std::cout << "\n=== Row major indexing : [row * ncol + col] ===\n\n";
    std::cout << "A [i * A.cols() + j]  = " << dataA[i * A.cols() + j] << "\n";
    std::cout << "At[i * At.cols() + j] = " << dataAtranspose[i * At.cols() + j] << "\n\n";

    // // Column-major
    // data[i + j * nrows] = A(i, j);  // Correct for column-major
    // A(2,0) should give 3.14
    std::cout << "\n=== Row major indexing : [row * ncol + col] ===\n\n";
    std::cout << "A [i + A.cols() * j]  = " << dataA[i + j * A.cols()] << "\n";
    std::cout << "At[i + At.cols() * j] = " << dataAtranspose[i + j * At.cols()] << "\n\n";

    /* Begin Problem 6 Actually Here */

    const int ntrials = 3;
    std::vector<int> sizes = {16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192};

    std::ofstream log("output/swap_timings.csv");
    log << "size,row_swap_time,col_swap_time\n";

    for (int N : sizes)
    {
        double total_row_time = 0.0;
        double total_col_time = 0.0;

        const std::string filename = "matrix_data.bin";

        for (int trial = 0; trial < ntrials; ++trial)
        {
            // Create matrix in column-major layout
            std::vector<double> matrix(N * N);
            for (int col = 0; col < N; ++col)
            {
                for (int row = 0; row < N; ++row)
                {
                    matrix[row + col * N] = static_cast<double>(row + col * N);
                }
            }

            // Write matrix to file
            std::ofstream out(filename, std::ios::binary);
            out.write(reinterpret_cast<char *>(&matrix[0]), N * N * sizeof(double));
            out.close();

            // Random rows and columns
            int i = std::rand() % N;
            int j = std::rand() % N;
            while (j == i)
                j = std::rand() % N;

            // Row swap timing
            std::fstream fileRow(filename, std::ios::in | std::ios::out | std::ios::binary);
            auto start_row = std::chrono::high_resolution_clock::now();
            swapRowsInFile(fileRow, N, N, i, j);
            auto stop_row = std::chrono::high_resolution_clock::now();
            fileRow.close();
            total_row_time += std::chrono::duration<double>(stop_row - start_row).count();

            // Column swap timing
            std::fstream fileCol(filename, std::ios::in | std::ios::out | std::ios::binary);
            auto start_col = std::chrono::high_resolution_clock::now();
            swapColsInFile(fileCol, N, N, i, j);
            auto stop_col = std::chrono::high_resolution_clock::now();
            fileCol.close();
            total_col_time += std::chrono::duration<double>(stop_col - start_col).count();

            std::remove(filename.c_str());
        }

        double avg_row = total_row_time / ntrials;
        double avg_col = total_col_time / ntrials;

        log << N << "," << avg_row << "," << avg_col << "\n";

        std::cout << "N = " << N
                  << " | Row swap avg = " << avg_row * 1e3 << " ms"
                  << " | Col swap avg = " << avg_col * 1e3 << " ms\n";
    }

    log.close();
    return 0;
}