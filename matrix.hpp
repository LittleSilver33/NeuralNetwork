
#pragma once

#include <vector>
#include <string>

class Matrix {

// TODO: Proper error handling in many methods

public:
    Matrix() {}
    Matrix(int r, int c = 1);
    Matrix(const Matrix& M);

    // Properties
    int Rows() const { return rows; }
    int Columns() const { return cols; }
    int Size() const { return data.size(); }
    bool isSquare() const { return rows == cols; }
    bool isSymmetric() const;

    // Access
    double Get(int r, int c) const { return data[r * cols + c]; }

    double& operator()(int r, int c) { return data[r * cols + c]; }
    const double& operator()(int r, int c) const { return data[r * cols + c]; }

    // Operations
    Matrix operator+(const Matrix& M) const { return Add(M); }
    Matrix operator-(const Matrix& M) const { return Sub(M); }
    Matrix operator*(const Matrix& M) const { return Mul(M); }
    Matrix operator*(double scalar) const { return ScalarMul(scalar); }

    Matrix Add(const Matrix& M) const;
    Matrix Sub(const Matrix& M) const;
    Matrix Mul(const Matrix& M) const;
    
    std::vector<double> Mul(const std::vector<double>& vec) const;

    Matrix ScalarMul(double scalar) const;
    Matrix ScalarDiv(double scalar) const;

    Matrix Transpose() const;
    Matrix Inverse() const;

    double Determinant() const;
    double Trace() const;

    Matrix ComponentwiseMul(const Matrix& M) const;
    Matrix ComponentwiseDiv(const Matrix& M) const;

    Matrix KroneckerMul(const Matrix& M) const;

    // Comparisons
    bool operator==(const Matrix& M) const;
    bool operator!=(const Matrix& M) const;

    // Manipulations
    Matrix HorizonalConcat(const Matrix& M) const;
    Matrix VerticalConcat(const Matrix& M) const;
    Matrix Submatrix(int rowStart, int rowEnd, int colStart, int colEnd) const;
    Matrix Reshape(int newRows, int newCols) const;
    Matrix Flatten() const { return Reshape(1, rows * cols); }

    // Debug
    std::string ToString() const;

    // Static
    static Matrix Identity(int size);

protected:
    int rows;
    int cols;
    
    std::vector<double> data;
};