/* AMATH 583
 * benprice
 * Apr 24, 2025
 * Homework 3
 * Problem 3
 *
 * === LEVEL 3 BLAS FUNCTION ===
 *
 * C++ function that computes
 * C <- a * A * B + b * C, where
 * A in R^(m x p),
 * B in R^(p x n),
 * C in R^(m x n),
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
 * === END LEVEL 3 BLAS FUNCTION ===
 *
 */
#include "ref_dgemm.hpp"

/* C++ function that computes
 * C <- a * A * B + b * C, where
 * A in R^(m x p),
 * B in R^(p x n),
 * C in R^(m x n),
 * and a,b in R */

void dgemm(double a,
           const std::vector<std::vector<double>> &A,
           const std::vector<std::vector<double>> &B,
           double b,
           std::vector<std::vector<double>> &C)
{
    size_t m = A.size();
    size_t p = A[0].size();
    size_t n = B[0].size();

    if (B.size() != p)
    {
        throw std::runtime_error("gemm error: number of rows of B must match number of columns of A.");
    }
    if (C.size() != m)
    {
        throw std::runtime_error("gemm error: number of rows of C must match number of rows of A.");
    }
    if (C[0].size() != n)
    {
        throw std::runtime_error("gemm error: number of columns of C must match number of columns of B.");
    }

    for (size_t i = 0; i < m; ++i)
    {
        if (A[i].size() != p)
        {
            throw std::runtime_error("gemm error: inconsistent row size in A.");
        }
    }
    for (size_t i = 0; i < p; ++i)
    {
        if (B[i].size() != n)
        {
            throw std::runtime_error("gemm error: inconsistent row size in B.");
        }
    }
    for (size_t i = 0; i < m; ++i)
    {
        if (C[i].size() != n)
        {
            throw std::runtime_error("gemm error: inconsistent row size in C.");
        }
    }

    // A = aAB + bC
    for (size_t i = 0; i < m; ++i)
    {
        for (size_t j = 0; j < n; ++j)
        {
            double temp = 0.0;
            for (size_t k = 0; k < p; ++k)
            {
                temp += A[i][k] * B[k][j];
            }
            C[i][j] = a * temp + b * C[i][j];
        }
    }
}
