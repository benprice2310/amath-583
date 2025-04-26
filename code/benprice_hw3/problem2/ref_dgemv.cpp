/* AMATH 583
 * benprice
 * Apr 24, 2025
 * Homework 3
 * Problem 2
 *
 * === LEVEL 2 BLAS FUNCTION ===
 *
 * C++ function that computes
 * y <- a * A * x + B * y where
 * A in R^(m x n),
 * x in R^n, y in R^m,
 * and a,b in R
 * 
 * Index convention:
 * A(i,j) = A[i][j]
 * [i] is the row (out of m)
 * [j] is the column (out of n)
 *
 * C++ function that calls L2BLAS
 * measures the performance for cases
 * n=2 to n=512.
 * Measure each n ntrial times.
 * Plot the average performance in FLOPS
 * for each case versus n
 *
 * Initialize with random values.
 * Check for and flag incorrect cases.
 * Test prior to submission.
 * 
 * === END LEVEL 2 BLAS FUNCTION ===
 *
 */
#include "ref_dgemv.hpp"
#include <iostream>

void dgemv(double a,
           const std::vector<std::vector<double>> &A,
           const std::vector<double> &x,
           double b,
           std::vector<double> &y)
{
    size_t m = A.size();
    size_t n = A[0].size();

    if (x.size() != n)
    {
        throw std::runtime_error("gemv error: x size must match number of columns of A.");
    }
    if (y.size() != m)
    {
        throw std::runtime_error("gemv error: y size must match number of rows of A.");
    }
    for (size_t i = 0; i < m; ++i)
    {
        if (A[i].size() != n)
        {
            throw std::runtime_error("gemv error: inconsistent row size in A.");
        }
    }

    for (size_t i = 0; i < m; ++i)
    {
        double temp = 0.0;
        for (size_t j = 0; j < n; ++j)
        {
            temp += A[i][j] * x[j];
        }
        y[i] = a * temp + b * y[i];
    }
}