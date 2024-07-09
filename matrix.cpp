#include "matrix.hpp"

#include <iomanip>
#include <sstream>

Matrix::Matrix(int r, int c = 1)
{
    this->rows = r;
    this->cols = c;
    data.reserve(r*c);

    int size = rows * cols;
    for (int i = 0; i < size; i++) {
        data.push_back(0.0);
    }
}

Matrix::Matrix(const Matrix& M)
{
    this->rows = M.rows;
    this->cols = M.cols;
    this->data = M.data;
}

bool Matrix::isSymmetric() const
{
    if (!isSquare()) {
        return false;
    }

    return *this == Transpose();
}

Matrix Matrix::Add(const Matrix& M) const
{
    if (M.rows != this->rows || M.cols != this->cols) {
        // Cannot Add, mismatched dimensions
        return Matrix();
    }

    Matrix result(rows, cols);

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            result(r,c) = this->Get(r,c) + M(r,c);
        }
    }

    return result;
}

Matrix Matrix::Sub(const Matrix& M) const
{
    return *this + (M * -1.0);
}

Matrix Matrix::Mul(const Matrix& M) const
{
    Matrix result(this->rows, M.cols);
    
    for (int r = 0; r < this->rows; r++) {
        for (int c = 0; c < M.cols; c++) {
            double sum = 0;
            for (int i = 0; i < this->cols; i++) {
                sum += this->Get(r,i) * M(i,c);
            }
            result(r,c) = sum;
        }
    }
    return result;
}

std::vector<double> Matrix::Mul(const std::vector<double>& vec) const
{
    if (vec.size() != this->cols) {
        // Cannot Multiply, mismatched dimensions
        return std::vector<double>();
    }

    std::vector<double> result;
    result.reserve(this->rows);

    for (int r = 0; r < this->rows; r++) {
        int sum = 0;
        for (int c = 0; c < this->cols; r++) {
            sum += vec[c] * this->Get(r,c);
        }
        result[r] = sum;
    }

    return result;
}

Matrix Matrix::ScalarMul(double scalar) const
{
    Matrix result(this->rows, this->cols);

    for (int r = 0; r < this->rows; r++) {
        for (int c = 0; c < this->cols; c++) {
            result(r,c) = this->Get(r,c) * scalar;
        }
    }
    
    return result;
}

Matrix Matrix::ScalarDiv(double scalar) const
{
    return ScalarMul(1.0 / scalar);
}

Matrix Matrix::Transpose() const
{
    Matrix result(this->cols, this->rows);

    for (int r = 0; r < this->rows; r++) {
        for (int c = 0; c < this->cols; c++) {
            result(c,r) = this->Get(r,c);
        }
    }

    return result;
}

Matrix Matrix::Inverse() const
{
    double det = Determinant();
    if (!isSquare() || det == 0.0) {
        // Matrix is not invertible
        return Matrix();
    }

    Matrix result(this->rows, this->rows);

    // Compute the matrix of minors
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->rows; j++) {
            Matrix minorMatrix = Submatrix(0, i, 0, j) + Submatrix(i + 1, this->rows, j + 1, this->rows);
            double minorDet = minorMatrix.Determinant();
            result(j, i) = ((i + j) % 2 == 0 ? 1 : -1) * minorDet;
        }
    }

    // Compute the adjugate matrix (transpose of the cofactor matrix)
    result = result.Transpose();

    // Divide each element by the determinant
    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j < this->rows; ++j) {
            result(i, j) /= det;
        }
    }

    return result;
}

double Matrix::Determinant() const
{
    if (!isSquare()) {
        // Cannot get determinant of matrix that is not square
        return 0.0;
    }

    if (rows == 1) {
        return data[0];
    }

    if (rows == 2) {
        return data[0] * data[3] - data[1] * data[2];
    }

    double det = 0.0;
    for (int c = 0; c < cols; c++) {
        Matrix submatrix = Submatrix(1, rows, 0, c);
        if (c + 1 < cols) {
            submatrix = submatrix + Submatrix(1, rows, c + 1, cols);
        }
        double cofactor = ((c % 2 == 0) ? 1 : -1) * data[c];
        det += cofactor * submatrix.Determinant();
    }

    return det;
}

double Matrix::Trace() const
{
    if (!isSquare()) {
        // Cannot get trace of matrix that is not square
        return 0.0;
    }

    double sum = 0.0;
    for (int r = 0; r < this->rows; r++) {
        sum += this->Get(r,r);
    }
    return sum;
}
// Hadamard Multiplication
Matrix Matrix::ComponentwiseMul(const Matrix& M) const
{
    if (M.rows != this->rows || M.cols != this->cols) {
        // Cannot Multiply Component-wise, mismatched dimensions
        return Matrix();
    }

    Matrix result(rows, cols);

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            result(r,c) = this->Get(r,c) * M(r,c);
        }
    }

    return result;
}

Matrix Matrix::ComponentwiseDiv(const Matrix& M) const
{
    if (M.rows != this->rows || M.cols != this->cols) {
        // Cannot Multiply Component-wise, mismatched dimensions
        return Matrix();
    }

    Matrix result(rows, cols);

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            result(r,c) = this->Get(r,c) / M(r,c);
        }
    }

    return result;
}

Matrix Matrix::KroneckerMul(const Matrix& M) const
{
    Matrix result(rows * M.rows, cols * M.cols);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            for (int mi = 0; mi < M.rows; ++mi) {
                for (int mj = 0; mj < M.cols; ++mj) {
                    result(i * M.rows + mi, j * M.cols + mj) = this->Get(i,j) * M(mi,mj);
                }
            }
        }
    }

    return result;
}

bool Matrix::operator==(const Matrix& M) const
{
    if (this->rows != M.rows || this->cols != M.cols) {
        return false;
    }

    for (int r = 0; r < this->rows; r++) {
        for (int c = 0; c < this->cols; c++) {
            if (this->Get(r,c) != M(r,c)) {
                return false;
            }
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix& M) const
{
    return !(*this == M);
}

Matrix Matrix::HorizonalConcat(const Matrix& M) const
{
    if (this->rows != M.Rows()) {
        // Number of rows must be same
        return Matrix();
    }

    Matrix result(this->rows, this->cols + M.Columns());
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            result(i, j) = this->Get(i, j);
        }
        for (int j = 0; j < M.Columns(); ++j) {
            result(i, this->cols + j) = M(i, j);
        }
    }

    return result;
}

Matrix Matrix::VerticalConcat(const Matrix& M) const
{
    if (this->cols != M.Columns()) {
        // Number of columns must be same
        return Matrix();
    }

    Matrix result(this->rows + M.Rows(), this->cols);
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < cols; j++) {
            result(i, j) = this->Get(i, j);
        }
    }
    for (int i = 0; i < M.Rows(); i++) {
        for (int j = 0; j < this->cols; j++) {
            result(this->rows + i, j) = M(i, j);
        }
    }

    return result;
}

Matrix Matrix::Submatrix(int rowStart, int rowEnd, int colStart, int colEnd) const
{
    if (rowEnd < rowStart || colEnd < colStart) {
        // Invalid parameters provided
        return Matrix();
    }

    Matrix result(rowEnd - rowStart, colEnd - colStart);
    for (int i = rowStart; i < rowEnd; ++i) {
        for (int j = colStart; j < colEnd; ++j) {
            result(i - rowStart, j - colStart) = this->Get(i, j);
        }
    }
    return result;
}

Matrix Matrix::Reshape(int newRows, int newCols) const
{
    if (newRows * newCols != this->rows * this->cols) {
        // Cannot reshape, incompatible dimensions
        return Matrix();
    }

    Matrix result(newRows, newCols);
    result.data = this->data;
    return result;
}

std::string Matrix::ToString() const
{
    std::stringstream stream;

    stream << "------------- START of Matrix -------------" << std::endl;

    for (int r = 0; r < this->rows; r++) {
        for (int c = 0; c < this->cols; c++) {
            stream << std::setprecision(2) << this->Get(r,c);
        }
        stream << std::endl;
    }
    
    stream << "-------------  END of Matrix  -------------" << std::endl;

    return stream.str();
}

Matrix Matrix::Identity(int size)
{
    Matrix result(size, size);
    
    for (int i = 0; i < size; i++) {
        result(i,i) = 1;
    }

    return result;
}