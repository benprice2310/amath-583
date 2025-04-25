/* AMATH 583
 * benprice
 * Apr 24, 2025
 * Homework 3
 * Problem 1
 *
 * === LEVEL 1 BLAS FUNCTION ===
 *
 * C++ function that computes
 * y <- ax + y
 * x,y in R^n
 * a in R
 *
 * C++ function that calls L1BLAS
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
 * === END LEVEL 1 BLAS FUNCTION ===
 *
 */
#include "ref_daxpy.hpp"

void daxpy(double a, const std::vector<double> &x, std::vector<double> &y)
{
    size_t n = x.size();
    for (size_t i = 0; i < n; i++)
    {
        y[i] += a * x[i];
    }
}