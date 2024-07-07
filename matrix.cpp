#include "matrix.hpp"

Matrix::Matrix(const Matrix& M)
{
    this->rows = M.rows;
    this->cols = M.cols;
    this->matrix = M.matrix;
}

bool Matrix::isSymmetric()
{
    if (!isSquare()) {
        return false;
    }

    return *this == Transpose();
}

Matrix Matrix::Add(const Matrix& M) const
{
    
}

Matrix Matrix::Sub(const Matrix& M) const
{

}
Matrix Matrix::Mul(const Matrix& M) const
{

}

std::vector<double> Matrix::Mul(const std::vector<double>& vec) const
{

}

Matrix Matrix::ScalarMul(double scalar) const
{

}
Matrix Matrix::ScalarDiv(double scalar) const
{

}

Matrix Matrix::Transpose() const
{
    
}

Matrix Matrix::Inverse() const
{
    
}

double Matrix::Determinant() const
{
    
}

double Matrix::Trace() const
{
    
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