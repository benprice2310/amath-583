// utils.hpp
#ifndef AM583_SP25_HW4_P3_UTILS_HPP
#define AM583_SP25_HW4_P3_UTILS_HPP

#include <vector>
#include <string>

void writeBinaryMatrix(const std::vector<double> &matrix, int N, const std::string &filename);

void readBinaryMatrix(std::vector<double> &matrix, int N, const std::string &filename);

std::vector<double> generateColMajorMatrix(int N);

#endif // utils.hpp
