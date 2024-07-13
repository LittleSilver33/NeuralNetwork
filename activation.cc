
#include "activation.h"

#include <cmath>

Matrix Activation::Activate(const Matrix& M) const {
    Matrix result(M.Rows(), M.Columns());
    for (int r = 0; r < M.Rows(); r++) {
        for (int c = 0; c < M.Columns(); c++) {
            result(r, c) = ActivationFunction(M(r, c));
        }
    }
    return result;
}

Matrix Activation::Derivative(const Matrix& M) const {
    Matrix result(M.Rows(), M.Columns());
    for (int r = 0; r < M.Rows(); r++) {
        for (int c = 0; c < M.Columns(); c++) {
            result(r, c) = DerivativeFunction(M(r, c));
        }
    }
    return result;
}

double Activation::ActivationFunction(double value) const {
    return 1.0 / (1.0 + std::exp(-value)); // Sigmoid
}

double Activation::DerivativeFunction(double value) const {
    double sigmoid = ActivationFunction(value);
    return sigmoid * (1 - sigmoid);
}
