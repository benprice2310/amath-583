// matrix_class.hpp
#ifndef AM583_SP25_HW4_P3_MATRIX_CLASS_HPP
#define AM583_SP25_HW4_P3_MATRIX_CLASS_HPP

#include <vector>
#include <stdexcept>
#include <cmath>
#include <iostream>
#include <iomanip>

// Row-major matrix class template
template <typename T>
class Matrix
{
private:
    std::vector<T> data_;
    int rows_;
    int cols_;

public:
    // Constructors
    Matrix(int rows, int cols, T val = T())
        : data_(rows * cols, val), rows_(rows), cols_(cols) {}

    // matrix_class.hpp (inside class Matrix<T>)
    Matrix(std::initializer_list<std::vector<T>> init)
    {
        rows_ = init.size();
        cols_ = init.begin()->size();
        data_.resize(rows_ * cols_);
        int i = 0;
        for (const auto &row : init)
        {
            if (row.size() != cols_)
                throw std::invalid_argument("Inconsistent row size in initializer list.");
            for (int j = 0; j < cols_; ++j)
            {
                data_[i * cols_ + j] = row[j];
            }
            ++i;
        }
    }

    // Accessors
    int rows() const { return rows_; }
    int cols() const { return cols_; }

    T &operator()(int i, int j)
    {
        return data_[i * cols_ + j];
    }

    const T &operator()(int i, int j) const
    {
        return data_[i * cols_ + j];
    }

    // Transpose
    Matrix<T> transpose() const
    {
        Matrix<T> result(cols_, rows_);
        for (int i = 0; i < rows_; ++i)
        {
            for (int j = 0; j < cols_; ++j)
            {
                result(j, i) = (*this)(i, j);
            }
        }
        return result;
    }

    // Infinity norm
    T infinityNorm() const
    {
        T maxSum = T();
        for (int i = 0; i < rows_; ++i)
        {
            T rowSum = T();
            for (int j = 0; j < cols_; ++j)
            {
                rowSum += std::abs((*this)(i, j));
            }
            if (rowSum > maxSum)
            {
                maxSum = rowSum;
            }
        }
        return maxSum;
    }

    // Matrix addition
    Matrix<T> operator+(const Matrix<T> &other) const
    {
        if (rows_ != other.rows_ || cols_ != other.cols_)
        {
            throw std::invalid_argument("Matrix dimensions must match for addition.");
        }
        Matrix<T> result(rows_, cols_);
        for (int i = 0; i < rows_ * cols_; ++i)
        {
            result.data_[i] = data_[i] + other.data_[i];
        }
        return result;
    }

    // Matrix multiplication
    Matrix<T> operator*(const Matrix<T> &other) const
    {
        if (cols_ != other.rows_)
        {
            throw std::invalid_argument("Matrix dimensions must be compatible for multiplication.");
        }
        Matrix<T> result(rows_, other.cols_);
        for (int i = 0; i < rows_; ++i)
        {
            for (int j = 0; j < other.cols_; ++j)
            {
                T sum = T();
                for (int k = 0; k < cols_; ++k)
                {
                    sum += (*this)(i, k) * other(k, j);
                }
                result(i, j) = sum;
            }
        }
        return result;
    }

    // Print matrix
    void print(int width = 10) const
    {
        for (int i = 0; i < rows_; ++i)
        {
            for (int j = 0; j < cols_; ++j)
            {
                std::cout << std::setw(width) << (*this)(i, j);
            }
            std::cout << "\n";
        }
    }

    // Get read-only access to the raw data vector
    const std::vector<T> &data() const
    {
        return data_;
    }
};

#endif // matrix_class.hpp