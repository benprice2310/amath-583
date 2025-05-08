// @uw.edu
// AMATH 483-583
// strassen.cpp : starter code for Strassen implementation

#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

template <typename T>
vector<vector<T>> addMatrix(const vector<vector<T>> &A, const vector<vector<T>> &B)
{
    int n = A.size();
    int m = A[0].size();
    vector<vector<T>> C(n, vector<T>(m));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
}

template <typename T>
vector<vector<T>> subtractMatrix(const vector<vector<T>> &A, const vector<vector<T>> &B)
{
    int n = A.size();
    int m = A[0].size();
    vector<vector<T>> C(n, vector<T>(m));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    return C;
}

template <typename T>
vector<vector<T>> strassenMultiply(const vector<vector<T>> &A, const vector<vector<T>> &B)
{
    int n = A.size();
    assert(n == (int)A[0].size() && n == (int)B.size() && n == (int)B[0].size());
    if (n == 1)
    {
        vector<vector<T>> C(1, vector<T>(1));
        C[0][0] = A[0][0] * B[0][0];
        return C;
    }
    int m = n / 2;
    // partition A and B into quadrants
    vector<vector<T>> A11(m, vector<T>(m)), A12(m, vector<T>(m)), A21(m, vector<T>(m)), A22(m, vector<T>(m));
    vector<vector<T>> B11(m, vector<T>(m)), B12(m, vector<T>(m)), B21(m, vector<T>(m)), B22(m, vector<T>(m));
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + m];
            A21[i][j] = A[i + m][j];
            A22[i][j] = A[i + m][j + m];
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + m];
            B21[i][j] = B[i + m][j];
            B22[i][j] = B[i + m][j + m];
        }
    }
    // seven Strassen products
    auto M1 = strassenMultiply(addMatrix(A11, A22), addMatrix(B11, B22));
    auto M2 = strassenMultiply(addMatrix(A21, A22), B11);
    auto M3 = strassenMultiply(A11, subtractMatrix(B12, B22));
    auto M4 = strassenMultiply(A22, subtractMatrix(B21, B11));
    auto M5 = strassenMultiply(addMatrix(A11, A12), B22);
    auto M6 = strassenMultiply(subtractMatrix(A21, A11), addMatrix(B11, B12));
    auto M7 = strassenMultiply(subtractMatrix(A12, A22), addMatrix(B21, B22));
    // combine intermediate results
    auto C11 = addMatrix(subtractMatrix(addMatrix(M1, M4), M5), M7);
    auto C12 = addMatrix(M3, M5);
    auto C21 = addMatrix(M2, M4);
    auto C22 = addMatrix(subtractMatrix(addMatrix(M1, M3), M2), M6);
    // assemble full C
    vector<vector<T>> C(n, vector<T>(n));
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            C[i][j] = C11[i][j];
            C[i][j + m] = C12[i][j];
            C[i + m][j] = C21[i][j];
            C[i + m][j + m] = C22[i][j];
        }
    }
    return C;
}

template <typename T>
void printMatrix(const vector<vector<T>> &matrix)
{
    int n = matrix.size();
    int m = matrix[0].size();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

// int
template vector<vector<int>> addMatrix<int>(const vector<vector<int>> &A, const vector<vector<int>> &B);
template vector<vector<int>> subtractMatrix<int>(const vector<vector<int>> &A, const vector<vector<int>> &B);
template vector<vector<int>> strassenMultiply<int>(const vector<vector<int>> &A, const vector<vector<int>> &B);
template void printMatrix<int>(const vector<vector<int>> &matrix);
// double
template vector<vector<double>> addMatrix<double>(const vector<vector<double>> &A, const vector<vector<double>> &B);
template vector<vector<double>> subtractMatrix<double>(const vector<vector<double>> &A, const vector<vector<double>> &B);
template vector<vector<double>> strassenMultiply<double>(const vector<vector<double>> &A, const vector<vector<double>> &B);
template void printMatrix<double>(const vector<vector<double>> &matrix);
