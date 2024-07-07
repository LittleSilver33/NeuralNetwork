
#pragma once

#include <vector>
#include <string>

class Matrix {

public:
    Matrix() {}
    Matrix(int r, int c);
    Matrix(const Matrix& M);

    // Properties
    int Rows() const { return rows; }
    int Columns() const { return cols; }
    bool isSquare() const { return rows == cols; }
    bool isSymmetric() const;

    // Access
    std::vector<double>& operator[](int index) { return data[index]; }
    const std::vector<double>& operator[](int index) const { return data[index]; }

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

    Matrix ComponentwiseAdd(const Matrix& M) const;
    Matrix ComponentwiseSub(const Matrix& M) const;
    Matrix ComponentwiseMul(const Matrix& M) const;
    Matrix ComponentwiseDiv(const Matrix& M) const;

    Matrix KroneckerMul(const Matrix& M) const;

    // Comparisons
    bool operator==(const Matrix& M) const;
    bool operator!=(const Matrix& M) const;

    // Manipulations
    Matrix HorizonalConcat(const Matrix& M) const;
    Matrix VerticalConcat(const Matrix& M) const;
    Matrix Reshape(int newRows, int newCols) const;
    Matrix Flatten() const { return Reshape(1, rows * cols); }

    // Debug
    std::string ToString() const;

    // Static
    static Matrix Identity(int size);

protected:
    int rows;
    int cols;
    
    std::vector<std::vector<double>> data;
};