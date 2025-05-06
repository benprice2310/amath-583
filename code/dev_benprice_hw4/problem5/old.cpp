

#include <iostream>
#include <iomanip>
#include "matrix_class.hpp"
#include "utils.hpp"

int main()
{
    std::cout << "=== Problem 3: Matrix Class Demonstration ===" << std::endl;

    // Construct 3x3 matrix with default values
    Matrix<double> A(3, 3, 1.0);
    std::cout << "\nMatrix A (3x3 filled with 1.0):" << std::endl;
    A.print();

    // Transpose of A
    Matrix<double> A_T = A.transpose();
    std::cout << "\nTranspose of A:" << std::endl;
    A_T.print();

    // Add matrices
    Matrix<double> B(3, 3, 2.0);
    Matrix<double> C = A + B;
    std::cout << "\nMatrix C = A + B (each element should be 3.0):" << std::endl;
    C.print();

    // Multiply matrices
    Matrix<double> D = A * B;
    std::cout << "\nMatrix D = A * B:" << std::endl;
    D.print();

    // Infinity norm of C
    std::cout << "\nInfinity norm of matrix C: " << C.infinityNorm() << std::endl;

    return 0;
}
