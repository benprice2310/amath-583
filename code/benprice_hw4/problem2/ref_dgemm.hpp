// ref_dgemm.hpp
#ifndef AM583_SP25_HW4_P2_REF_DGEMM_HPP
#define AM583_SP25_HW4_P2_REF_DGEMM_HPP

#include <vector>

// templated to be 2D array
template <typename T>
void mm_ijk(T a, const std::vector<std::vector<T>> &A, const std::vector<std::vector<T>> &B, T b, std::vector<std::vector<T>> &C, int m, int p, int n)
{
    // i in [0, m-1]    // i : m
    // k in [0, p-1]    // k : p
    // j in [0, n-1]    // j : n

    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            T sum = 0;
            for (int k = 0; k < p; ++k)
            {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = a * sum + b * C[i][j];
        }
    }
}

// overload forward mapped column major indexing
template <typename T>
void mm_ijk(T a, const std::vector<T> &A, const std::vector<T> &B, T b, std::vector<T> &C, int m, int p, int n)
{
    // i in [0, m-1]    // i : m
    // k in [0, p-1]    // k : p
    // j in [0, n-1]    // j : n

    // A in m x p       // A(i,k) -> A[i + k * m]
    // B in p x n       // B(k,j) -> B[k + j * p]
    // C in m x n       // C(i,j) -> C[i + j * m]

    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            T sum = 0;
            for (int k = 0; k < p; ++k)
            {
                sum += A[i + k * m] * B[k + j * p];
            }
            C[i + j * m] = a * sum + b * C[i + j * m];
        }
    }
}

template <typename T>
void mm_jki(T a, const std::vector<T> &A, const std::vector<T> &B, T b, std::vector<T> &C, int m, int p, int n)
{
    // i in [0, m-1]    // i : m
    // k in [0, p-1]    // k : p
    // j in [0, n-1]    // j : n

    // A in m x p       // A(i,k) -> A[i + k * m]
    // B in p x n       // B(k,j) -> B[k + j * p]
    // C in m x n       // C(i,j) -> C[i + j * m]

    // First scale C by b
    for (int i = 0; i < m * n; ++i)
    {
        C[i] *= b;
    }

    for (int j = 0; j < n; ++j)
    {
        for (int k = 0; k < p; ++k)
        {
            for (int i = 0; i < m; ++i)
            {
                C[i + j * m] += a * A[i + k * m] * B[k + j * p];
            }
        }
    }
}

template <typename T>
void mm_kij(T a, const std::vector<T> &A, const std::vector<T> &B, T b, std::vector<T> &C, int m, int p, int n)
{
    // i in [0, m-1]    // i : m
    // k in [0, p-1]    // k : p
    // j in [0, n-1]    // j : n

    // A in m x p       // A(i,k) -> A[i + k * m]
    // B in p x n       // B(k,j) -> B[k + j * p]
    // C in m x n       // C(i,j) -> C[i + j * m]

    // First scale C by b
    for (int i = 0; i < m * n; ++i)
    {
        C[i] *= b;
    }

    // Perform GEMM in kij order
    for (int k = 0; k < p; ++k)
    {
        for (int i = 0; i < m; ++i)
        {
            T Aik = A[i + k * m]; // Cache A(i,k)
            for (int j = 0; j < n; ++j)
            {
                C[i + j * m] += a * Aik * B[k + j * p];
            }
        }
    }
}

#endif // ref_dgemm.hpp