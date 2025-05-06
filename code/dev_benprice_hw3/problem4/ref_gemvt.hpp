#ifndef REF_GEMVT_HPP
#define REF_GEMVT_HPP

#include <vector>

template <typename T>
void gemv(T a,
          const std::vector<std::vector<T>> &A,
          const std::vector<T> &x,
          T b,
          std::vector<T> &y)
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
        T temp = T(0);
        for (size_t j = 0; j < n; ++j)
        {
            temp += A[i][j] * x[j];
        }
        y[i] = a * temp + b * y[i];
    }
}

#endif // REF_GEMVT_HPP