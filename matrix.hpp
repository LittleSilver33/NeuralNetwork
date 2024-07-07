
#pragma once

#include <vector>
#include <string>

class Matrix {

public:
    Matrix() {}
    Matrix(int r, int c) : rows(r), cols(c) {}

    int Rows() { return rows; }
    int Columns() { return cols; }
    bool isSquare();
    bool isSymmetric();

    std::vector<double>& operator[](int index) { return matrix[index]; }
    const std::vector<double>& operator[](int index) const { return matrix[index]; }

    Matrix operator+(const Matrix& M) const { return Add(M); }
    Matrix operator-(const Matrix& M) const { return Sub(M); }
    Matrix operator*(const Matrix& M) const { return Mul(M); } // Matrix multiplication
    Matrix operator*(double scalar) const { return ScalarMul(scalar); } // Scalar multiplication

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

    bool operator==(const Matrix& M) const;
    bool operator!=(const Matrix& M) const;

    Matrix reshape(int newRows, int newCols) const;
    Matrix flatten() const { return reshape(1, rows * cols); }

    std::string ToString() const;

protected:
    int rows;
    int cols;
    
    std::vector<std::vector<double>> matrix;
};