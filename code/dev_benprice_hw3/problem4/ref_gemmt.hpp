#ifndef REF_GEMMT_HPP
#define REF_GEMMT_HPP

#include <vector>

template <typename T>
void gemm(T a,
          const std::vector<std::vector<T>> &A,
          const std::vector<std::vector<T>> &B,
          T b,
          std::vector<std::vector<T>> &C)
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

    // Perform the matrix multiplication and accumulate into C
    for (std::size_t i = 0; i < m; ++i)
    {
        for (std::size_t j = 0; j < n; ++j)
        {
            T temp = T(0);
            for (std::size_t k = 0; k < p; ++k)
            {
                temp += A[i][k] + B[k][j];
            }
            C[i][j] = a * temp + b * C[i][j];
        }
    }
}

#endif // REF_GEMMT_HPP