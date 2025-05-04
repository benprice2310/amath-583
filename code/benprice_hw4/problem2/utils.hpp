// utils.hpp
#ifndef AM583_SP25_HW4_P2_UTILS_HPP
#define AM583_SP25_HW4_P2_UTILS_HPP

#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>
#include <string>
#include <random>
#include <type_traits>

// Floating-point version
template <typename T>
typename std::enable_if<std::is_floating_point<T>::value, std::vector<T>>::type
generateRandomMatrix(int rows, int cols, T lb = T(0), T ub = T(1))
{
    std::vector<T> mat(rows * cols);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<T> dist(lb, ub);
    for (T &val : mat)
        val = dist(gen);
    return mat;
}

// Integer version
template <typename T>
typename std::enable_if<std::is_integral<T>::value, std::vector<T>>::type
generateRandomMatrix(int rows, int cols, T lb = T(0), T ub = T(1))
{
    std::vector<T> mat(rows * cols);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<T> dist(lb, ub);
    for (T &val : mat)
        val = dist(gen);
    return mat;
}

// Print a 2D std::vector with labeled rows and aligned columns
template <typename T>
void print2DRowMajorMatrix(const std::vector<std::vector<T>> &vec, int width = 10, const std::string &label = "")
{
    if (!label.empty())
    {
        std::cout << label << "\n";
    }

    int rows = vec.size();
    int cols = (rows > 0) ? vec[0].size() : 0;

    // Header
    std::cout << std::setw(width) << " " << " |";
    for (int j = 0; j < cols; ++j)
    {
        std::cout << std::setw(width) << std::right << j;
    }
    std::cout << "\n";

    // Divider
    std::cout << std::setw(width) << std::setfill('-') << "" << "-|";
    for (int j = 0; j < cols; ++j)
    {
        std::cout << std::setw(width) << std::setfill('-') << "";
    }
    std::cout << std::setfill(' ') << "\n";

    // Rows
    for (int i = 0; i < rows; ++i)
    {
        std::ostringstream rowLabel;
        rowLabel << "Row " << i;
        std::cout << std::setw(width) << std::left << rowLabel.str() << " |";
        for (int j = 0; j < cols; ++j)
        {
            std::cout << std::setw(width) << std::right << vec[i][j];
        }
        std::cout << "\n";
    }
}

// Print a flattened column-major vector as a 2D matrix
template <typename T>
void printColumnMajorVectorMatrix(const std::vector<T> &vec, int rows, int cols, int width = 10, const std::string &label = "")
{
    if (!label.empty())
    {
        std::cout << label << "\n";
    }

    // Header
    std::cout << std::setw(width) << " " << " |";
    for (int j = 0; j < cols; ++j)
    {
        std::cout << std::setw(width) << std::right << j;
    }
    std::cout << "\n";

    // Divider
    std::cout << std::setw(width) << std::setfill('-') << "" << "-|";
    for (int j = 0; j < cols; ++j)
    {
        std::cout << std::setw(width) << std::setfill('-') << "";
    }
    std::cout << std::setfill(' ') << "\n";

    // Rows
    for (int i = 0; i < rows; ++i)
    {
        std::ostringstream rowLabel;
        rowLabel << "Row " << i;
        std::cout << std::setw(width) << std::left << rowLabel.str() << " |";
        for (int j = 0; j < cols; ++j)
        {
            std::cout << std::setw(width) << std::right << vec[i + j * rows];
        }
        std::cout << "\n";
    }
}

// Print a flattened row-major vector as a 2D matrix
template <typename T>
void printRowMajorVectorMatrix(const std::vector<T> &vec, int rows, int cols, int width = 10, const std::string &label = "")
{
    if (!label.empty())
    {
        std::cout << label << "\n";
    }

    // Header
    std::cout << std::setw(width) << " " << " |";
    for (int j = 0; j < cols; ++j)
    {
        std::cout << std::setw(width) << std::right << j;
    }
    std::cout << "\n";

    // Divider
    std::cout << std::setw(width) << std::setfill('-') << "" << "-|";
    for (int j = 0; j < cols; ++j)
    {
        std::cout << std::setw(width) << std::setfill('-') << "";
    }
    std::cout << std::setfill(' ') << "\n";

    // Rows
    for (int i = 0; i < rows; ++i)
    {
        std::ostringstream rowLabel;
        rowLabel << "Row " << i;
        std::cout << std::setw(width) << std::left << rowLabel.str() << " |";
        for (int j = 0; j < cols; ++j)
        {
            std::cout << std::setw(width) << std::right << vec[i * cols + j];
        }
        std::cout << "\n";
    }
}

// Print a formatted section header to the console
inline void printSectionTitle(const std::string &title, int width = 60)
{
    std::cout << "\n"
              << std::string(width, '=') << "\n";
    int pad = (width - static_cast<int>(title.length())) / 2;
    std::cout << std::string(pad, ' ') << title << "\n";
    std::cout << std::string(width, '=') << "\n";
}

// Print a lighter section header
inline void printHeader(const std::string &subtitle, int width = 60)
{
    std::cout << "\n"
              << std::string(width, '-') << "\n";
    int pad = (width - static_cast<int>(subtitle.length())) / 2;
    std::cout << std::string(pad, ' ') << subtitle << "\n";
    std::cout << std::string(width, '-') << "\n";
}

// Print a small left-aligned subheader
inline void printSubheaderLeft(const std::string &text, int indent = 2)
{
    std::cout << "\n"
              << std::string(indent, ' ') << "=== " << text << " ===\n";
}

#endif // utils.hpp
