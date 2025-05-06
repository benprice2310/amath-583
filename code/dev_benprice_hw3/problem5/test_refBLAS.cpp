#include <iostream>
#include <vector>
#include "refBLAS.hpp"

int main() {
    // Test axpy
    std::vector<double> x = {1.0, 2.0, 3.0};
    std::vector<double> y = {4.0, 5.0, 6.0};
    axpy(2.0, x, y);
    std::cout << "axpy result: ";
    for (auto v : y) std::cout << v << " ";
    std::cout << "\n";

    // Test gemv
    std::vector<std::vector<double>> A = {{1.0, 2.0}, {3.0, 4.0}};
    std::vector<double> x2 = {1.0, 1.0};
    std::vector<double> y2 = {0.0, 0.0};
    gemv(1.0, A, x2, 0.0, y2);
    std::cout << "gemv result: ";
    for (auto v : y2) std::cout << v << " ";
    std::cout << "\n";

    // Test gemm
    std::vector<std::vector<double>> B = {{5.0, 6.0}, {7.0, 8.0}};
    std::vector<std::vector<double>> C = {{0.0, 0.0}, {0.0, 0.0}};
    gemm(1.0, A, B, 0.0, C);
    std::cout << "gemm result:\n";
    for (const auto& row : C) {
        for (auto v : row) std::cout << v << " ";
        std::cout << "\n";
    }

    return 0;
}