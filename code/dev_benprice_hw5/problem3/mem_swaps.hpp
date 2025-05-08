#include <vector>
#include <utility>   // for std::pair
#include <cstdlib>   // for std::rand()
#include <algorithm> // for std::swap

// Swap two rows i and j in an nRows × nCols matrix stored column-major
// matrix[k] represents element (row = k % nRows, col = k / nRows).
inline void swapRows(std::vector<double> &matrix,
                     int nRows, int nCols,
                     int i, int j)
{
    for (int c = 0; c < nCols; ++c)
    {
        // index of (i,c) is c*nRows + i
        std::swap(matrix[c * nRows + i],
                  matrix[c * nRows + j]);
    }
}

// Swap two columns i and j in an nRows × nCols matrix stored column-major.
// Columns are contiguous blocks of length nRows.
inline void swapCols(std::vector<double> &matrix,
                     int nRows, int nCols,
                     int i, int j)
{
    int off_i = i * nRows;
    int off_j = j * nRows;
    for (int r = 0; r < nRows; ++r)
    {
        std::swap(matrix[off_i + r],
                  matrix[off_j + r]);
    }
}

// Utility to pick two distinct random indices in [0..n)
inline std::pair<int, int> getRandomIndices(int n)
{
    int i = std::rand() % n;
    int j = std::rand() % (n - 1);
    if (j >= i)
        ++j;
    return {i, j};
}