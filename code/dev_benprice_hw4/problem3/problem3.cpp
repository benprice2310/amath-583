// problem3.cpp
#include <iostream>
#include <iomanip>
#include "matrix_class.hpp"
#include "utils.hpp"
int main()
{
    std::cout << "=== Problem 3: Matrix Class Demonstration ===" << std::endl;

    // Construct matrix A with more interesting data
    Matrix<double> A({{1.0, 2.0, 3.0},
                      {-4.0, 0.0, 5.5},
                      {3.14, -2.71, 0.0}});

    std::cout << "\nMatrix A:" << std::endl;
    A.print();

    // Transpose of A
    Matrix<double> A_T = A.transpose();
    std::cout << "\nTranspose of A:" << std::endl;
    A_T.print();

    // Construct matrix B with a pattern
    Matrix<double> B({{0.5, -1.0, 2.0},
                      {3.0, 1.5, -2.5},
                      {0.0, 4.0, 1.0}});

    std::cout << "\nMatrix B:" << std::endl;
    B.print();

    // Add matrices
    Matrix<double> C = A + B;
    std::cout << "\nMatrix C = A + B:" << std::endl;
    C.print();

    // Multiply matrices
    Matrix<double> D = A * B;
    std::cout << "\nMatrix D = A * B:" << std::endl;
    D.print();

    // Infinity norm of C
    std::cout << "\nInfinity norm of matrix C: " << C.infinityNorm() << std::endl;

    return 0;
}