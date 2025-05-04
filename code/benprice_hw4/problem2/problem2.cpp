// problem2.cpp

#include <iostream>
#include <chrono>
#include <vector>
#include <iomanip>
#include "ref_dgemm.hpp"
#include "utils.hpp"

const int PRINT_WIDTH = 6;

int main()
{
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
    std::vector<int> C_cm{2, 2, 0, 2, 2, -4, -4, 5, -4, -5, 1, 4, 2, -3, -1};

    std::cout << "\n=== Sizes ===\n";
    std::cout << "size A: [m, p] = [" << A_2D.size() << ", " << A_2D[0].size() << "]\n";
    std::cout << "size B: [p, n] = [" << B_2D.size() << ", " << B_2D[0].size() << "]\n";
    std::cout << "size C: [m, n] = [" << C_2D.size() << ", " << C_2D[0].size() << "]\n\n";

    // printSectionHeader("A 2D Matrix");
    // print2DVector(A_2D);
    std::cout << "\n";
    printSectionTitle("Initial Parameters");
    printSubheaderLeft("A Column Major Flattend Matrix");
    printColumnMajorVectorMatrix(A_cm, m, p);
    printSubheaderLeft("B Column Major Flattend Matrix");
    printColumnMajorVectorMatrix(B_cm, p, n);
    printSubheaderLeft("C Column Major Flattend Matrix");
    printColumnMajorVectorMatrix(C_cm, m, n);

    return 0;
}