// utils.cpp
#include <iostream>
#include <fstream>
#include "utils.hpp"

void writeBinaryMatrix(const std::vector<double> &matrix, int N, const std::string &filename)
{
    std::ofstream out(filename, std::ios::binary);
    if (!out)
    {
        std::cerr << "Failed to open file for writing: " << filename << std::endl;
        return;
    }
    out.write(reinterpret_cast<const char *>(matrix.data()), sizeof(double) * matrix.size());
    out.close();
}

void readBinaryMatrix(std::vector<double> &matrix, int N, const std::string &filename)
{
    std::ifstream in(filename, std::ios::binary);
    if (!in)
    {
        std::cerr << "Failed to open file for reading: " << filename << std::endl;
        return;
    }
    in.read(reinterpret_cast<char *>(matrix.data()), sizeof(double) * matrix.size());
    in.close();
}

std::vector<double> generateColMajorMatrix(int N)
{
    std::vector<double> mat(N * N);
    for (int j = 0; j < N; ++j)
    {
        for (int i = 0; i < N; ++i)
        {
            mat[i + j * N] = static_cast<double>(i + j * N);
        }
    }
    return mat;
}
