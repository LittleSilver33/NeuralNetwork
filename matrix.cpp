#include "matrix.hpp"

Matrix::Matrix(int r, int c)
{
    this->rows = r;
    this->cols = c;

    data.reserve(r);
    for(int i = 0; i < r; i++) {
        data[i].reserve(c);
        // Initialize Values to 0
        for(int j = 0; j < c; j++) {
            data[i].push_back(0.0);
        }
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

    Matrix sum(rows, cols);

    for(int r = 0; r < rows; r++) {
        for(int c = 0; c < cols; c++) {
            sum[r][c] = data[r][c] + M[r][c];
        }
    }

    return sum;
}

Matrix Matrix::Sub(const Matrix& M) const
{
    return *this + (M * -1.0);
}

Matrix Matrix::Mul(const Matrix& M) const
{
    Matrix product(this->rows, M.cols);
    
    for(int r = 0; r < this->rows; r++) {
        for(int c = 0; c < M.cols; c++) {
            double sum = 0;
            for(int i = 0; i < this->cols; i++) {
                sum += data[r][i] * M[i][c];
            }
            product[r][c] = sum;
        }
    }
    return product;
}

std::vector<double> Matrix::Mul(const std::vector<double>& vec) const
{
    if (vec.size() != this->cols) {
        // Cannot Multiply, mismatched dimensions
        return std::vector<double>();
    }

    std::vector<double> product;
    product.reserve(this->rows);

    for(int r = 0; r < this->rows; r++) {
        int sum = 0;
        for(int c = 0; c < this->cols; r++) {
            sum += vec[c] * data[r][c];
        }
        product[r] = sum;
    }

    return product;
}

Matrix Matrix::ScalarMul(double scalar) const
{
    Matrix product(this->rows, this->cols);

    for(int r = 0; r < this->rows; r++) {
        for(int c = 0; c < this->cols; c++) {
            product[r][c] = data[r][c] * scalar;
        }
    }
    
    return product;
}
Matrix Matrix::ScalarDiv(double scalar) const
{
    return ScalarMul(1.0 / scalar);
}

Matrix Matrix::Transpose() const
{
    Matrix transpose(this->cols, this->rows);

    for(int r = 0; r < this->rows; r++) {
        for(int c = 0; c < this->cols; c++) {
            transpose[c][r] = data[r][c];
        }
    }

    return transpose;
}

Matrix Matrix::Inverse() const
{
    if(!isSquare() || Determinant() == 0.0) {
        // Matrix is not invertible
        return Matrix();
    }
    
    // TODO: Implement

}

double Matrix::Determinant() const
{
    if(!isSquare()) {
        // Cannot get determinant of matrix that is not square
        return 0.0;
    }
}

double Matrix::Trace() const
{
    if(!isSquare()) {
        // Cannot get trace of matrix that is not square
        return 0.0;
    }

    double sum = 0.0;
    for(int r = 0; r < this->rows; r++) {
        sum += data[r][r];
    }
    return sum;
}

Matrix Matrix::ComponentwiseAdd(const Matrix& M) const
{
    
}

Matrix Matrix::ComponentwiseSub(const Matrix& M) const
{
    
}

Matrix Matrix::ComponentwiseMul(const Matrix& M) const
{
    
}

Matrix Matrix::ComponentwiseDiv(const Matrix& M) const
{
    
}

Matrix Matrix::KroneckerMul(const Matrix& M) const
{

}

bool Matrix::operator==(const Matrix& M) const
{
    
}

bool Matrix::operator!=(const Matrix& M) const
{
    
}

Matrix Matrix::HorizonalConcat(const Matrix& M) const
{

}

Matrix Matrix::VerticalConcat(const Matrix& M) const
{

}

Matrix Matrix::Reshape(int newRows, int newCols) const
{
    
}

std::string Matrix::ToString() const
{
    
}

Matrix Matrix::Identity(int size)
{

}