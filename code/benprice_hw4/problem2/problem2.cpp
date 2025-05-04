// problem7.cpp

#include <iostream>
#include <ctime>
#include <iomanip>
#include <vector>
#include "ref_dgemm.hpp"

const int PRINT_WIDTH = 10;

void test2Dtemplate()
{
    int m = 5;
    int n = 3;
    int p = 4;

    int a = 7;
    int b = 8;

    std::vector<std::vector<int>> A{
        {-4, -5, 1, -4},
        {-4, -1, -2, -4},
        {-1, 0, -1, -1},
        {4, -1, -5, -3},
        {3, 2, 5, 0}};
    std::vector<std::vector<int>> B{
        {-2, 3, 5},
        {-5, 3, -1},
        {5, -1, 5},
        {-5, 1, -2}};
    std::vector<std::vector<int>> C{
        {2, -4, 1},
        {2, -4, 4},
        {0, 5, 2},
        {2, -4, -3},
        {2, -5, -1}};

    std::cout << "sizes   [m, n, p]  = [" << m << ", " << n << ", " << p << "]\n\n";

    std::cout << "size A: [row, col] = [" << A.size() << ", " << A[0].size() << "]\n";
    std::cout << "size B: [row, col] = [" << B.size() << ", " << B[0].size() << "]\n";
    std::cout << "size C: [row, col] = [" << C.size() << ", " << C[0].size() << "]\n\n";

    std::cout << "Address A(0,0)  :  ( " << &A[0][0] << " )_16  :  ( " << reinterpret_cast<std::uintptr_t>(&A[0][0]) << " )_10 \n";
    std::cout << "Address A(0,1)  :  ( " << &A[0][1] << " )_16  :  ( " << reinterpret_cast<std::uintptr_t>(&A[0][1]) << " )_10 \n";
    std::cout << "Address A(0,3)  :  ( " << &A[0][3] << " )_16  :  ( " << reinterpret_cast<std::uintptr_t>(&A[0][3]) << " )_10 \n";
    std::cout << "Address A(1,0)  :  ( " << &A[1][0] << " )_16  :  ( " << reinterpret_cast<std::uintptr_t>(&A[1][0]) << " )_10 \n";

    std::cout << "\n=== C Initial Value ===\n";
    for (int i = 0; i < C.size(); ++i)
    {
        for (int j = 0; j < C[i].size(); ++j)
        {
            std::cout << "  " << std::setw(PRINT_WIDTH) << C[i][j];
        }
        std::cout << "\n";
    }

    mm_ijk(a, A, B, b, C, m, p, n);

    std::cout << "\n=== C = a*A*B + b*C ===\n";
    for (int i = 0; i < C.size(); ++i)
    {
        for (int j = 0; j < C[i].size(); ++j)
        {
            std::cout << "  " << std::setw(PRINT_WIDTH) << C[i][j];
        }
        std::cout << "\n";
    }
}

int main()
{
    std::time_t start_time;                    // variable start_time
    std::time_t *ptr_start_time = &start_time; // address of start_time. Unnecessary, just practicing

    std::time(ptr_start_time);
    std::cout << "\n\n=== AMATH 583. Problem 2. Begin. ===\n";
    std::cout << std::asctime(std::localtime(ptr_start_time)) << "\n";
    // std::cout << std::asctime(std::localtime(start_time)) << "\n";

    int m = 5;
    int n = 3;
    int p = 4;

    int a = 7;
    int b = 8;

    // reduced scope 2-dimensional std::vector for testing
    test2Dtemplate();

    std::cout << "\n\n\n==================================================\n";
    std::cout << "=== USING FORWARD MAPPED COLUMN MAJOR INDEXING ===\n";
    std::cout << "==================================================\n";

    std::vector<int> A{-4, -4, -1, 4, 3, -5, -1, 0, -1, 2, 1, -2, -1, -5, 5, -4, -4, -1, -3, 0};
    std::vector<int> B{-2, 5, 5, -5, 3, -3, -1, 1, 5, -1, 5, -2};
    std::vector<int> C{2, 2, 0, 2, 2, -4, -4, 5, -4, -5, 1, 4, 2, -3, -1};

    std::cout << "\n=== C Initial Value ===\n";
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            std::cout << "  " << std::setw(PRINT_WIDTH) << C[i + j * m];
        }
        std::cout << "\n";
    }

    mm_ijk(a, A, B, b, C, m, p, n);

    std::cout << "\n=== C = a*A*B + b*C ===\n";
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            std::cout << "  " << std::setw(PRINT_WIDTH) << C[i + j * m];
        }
        std::cout << "\n";
    }

    std::cout << "\n\n=== AMATH 583. Problem 2. End. ===\n\n";
    return 0;
}