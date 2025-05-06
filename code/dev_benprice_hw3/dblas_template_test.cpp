#include <iostream>
#include <vector>
#include "ref_axpyt.hpp"
#include "ref_gemvt.hpp"
#include "ref_gemmt.hpp"

int main()
{
    // Test axpy
    std::vector<double> x = {1.0, 2.0, 3.0};
    std::vector<double> y = {4.0, 5.0, 6.0};
    double a = 2.0;

    axpy(a, x, y);

    std::cout << "Result of axpy (y = 2x + y): ";
    for (const auto &val : y)
        std::cout << val << " ";
    std::cout << "\n";

    // Test gemv
    std::vector<std::vector<double>> A = {{1.0, 2.0}, {3.0, 4.0}};
    std::vector<double> x2 = {1.0, 1.0};
    std::vector<double> y2 = {0.0, 0.0};

    gemv(1.0, A, x2, 0.0, y2);

    std::cout << "Result of gemv (y = Ax): ";
    for (const auto &val : y2)
        std::cout << val << " ";
    std::cout << "\n";

    // Test gemm
    std::vector<std::vector<double>> B = {{5.0, 6.0}, {7.0, 8.0}};
    std::vector<std::vector<double>> C = {{0.0, 0.0}, {0.0, 0.0}};

    gemm(1.0, A, B, 0.0, C);

    std::cout << "Result of gemm (C = AB):\n";
    for (const auto &row : C)
    {
        for (const auto &val : row)
            std::cout << val << " ";
        std::cout << "\n";
    }

    return 0;
}