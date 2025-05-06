// utils.hpp
#ifndef AM583_SP25_HW4_P3_UTILS_HPP
#define AM583_SP25_HW4_P3_UTILS_HPP

#include <vector>
#include <string>
#include <iostream>
#include <vector>
#include <iomanip>

void writeBinaryMatrix(const std::vector<double> &matrix, int N, const std::string &filename);

void readBinaryMatrix(std::vector<double> &matrix, int N, const std::string &filename);

std::vector<double> generateColMajorMatrix(int N);

template <typename T>
void printVector(const std::vector<T> &vec)
{
    std::cout << "[ ";
    for (std::size_t i = 0; i < vec.size() - 1; ++i)
    {
        std::cout << std::fixed << std::setprecision(3) << vec[i] << ", ";
    }
    std::cout << std::fixed << std::setprecision(3) << vec.back() << " ]\n";
}

#endif // utils.hpp
