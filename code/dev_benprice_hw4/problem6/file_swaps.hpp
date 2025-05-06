// file_swaps.hpp
#ifndef AM583_SP25_HW4_P6_FILE_SWAPS_HPP
#define AM583_SP25_HW4_P6_FILE_SWAPS_HPP

#include <fstream>
#include <vector>

void swapRowsInFile(std::fstream &file, int nRows, int nCols, int i, int j)
{
    if (i == j)
        return;

    std::vector<double> row_i(nCols);
    std::vector<double> row_j(nCols);

    file.seekg(i * nCols * sizeof(double), std::ios::beg);
    file.read(reinterpret_cast<char *>(row_i.data()), nCols * sizeof(double));

    file.seekg(j * nCols * sizeof(double), std::ios::beg);
    file.read(reinterpret_cast<char *>(row_j.data()), nCols * sizeof(double));

    file.seekp(i * nCols * sizeof(double), std::ios::beg);
    file.write(reinterpret_cast<char *>(row_j.data()), nCols * sizeof(double));

    file.seekp(j * nCols * sizeof(double), std::ios::beg);
    file.write(reinterpret_cast<char *>(row_i.data()), nCols * sizeof(double));
}

void swapColsInFile(std::fstream &file, int nRows, int nCols, int i, int j)
{
    if (i == j)
        return;

    for (int row = 0; row < nRows; ++row)
    {
        double val_i, val_j;

        file.seekg((row * nCols + i) * sizeof(double), std::ios::beg);
        file.read(reinterpret_cast<char *>(&val_i), sizeof(double));

        file.seekg((row * nCols + j) * sizeof(double), std::ios::beg);
        file.read(reinterpret_cast<char *>(&val_j), sizeof(double));

        file.seekp((row * nCols + i) * sizeof(double), std::ios::beg);
        file.write(reinterpret_cast<char *>(&val_j), sizeof(double));

        file.seekp((row * nCols + j) * sizeof(double), std::ios::beg);
        file.write(reinterpret_cast<char *>(&val_i), sizeof(double));
    }
}

#endif // file_swaps.hpp