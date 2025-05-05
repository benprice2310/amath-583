// problem5.cpp
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <chrono>
#include <cmath>
#include "matrix_class.hpp"
#include "utils.hpp"

int main()
{
    std::cout << "=== Problem 5: Matrix IO Bandwidth ===" << std::endl;

    std::vector<int> sizes = {32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384};

    std::ofstream csv("output/io_bandwidth.csv");
    csv << "N,write_bandwidth_Bps,read_bandwidth_Bps\n";

    for (int N : sizes)
    {
        size_t num_bytes = N * N * sizeof(double);
        std::vector<double> matrix = generateColMajorMatrix(N);
        std::vector<double> buffer(N * N);
        std::string filename = "output/matrix_" + std::to_string(N) + ".bin";

        auto start_write = std::chrono::high_resolution_clock::now();
        writeBinaryMatrix(matrix, N, filename);
        auto end_write = std::chrono::high_resolution_clock::now();

        auto start_read = std::chrono::high_resolution_clock::now();
        readBinaryMatrix(buffer, N, filename);
        auto end_read = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> write_time = end_write - start_write;
        std::chrono::duration<double> read_time = end_read - start_read;

        double write_bandwidth = num_bytes / write_time.count();
        double read_bandwidth = num_bytes / read_time.count();

        std::cout << std::fixed << std::setprecision(2);
        std::cout << std::setw(6) << "N = " << std::setw(5) << N
                  << " | Write BW = " << std::setw(8) << write_bandwidth / 1e6 << " MB/s"
                  << " | Read BW = " << std::setw(8) << read_bandwidth / 1e6 << " MB/s" << std::endl;

        csv << N << "," << write_bandwidth << "," << read_bandwidth << "\n";
    }

    csv.close();
    return 0;
}