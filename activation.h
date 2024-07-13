
#pragma once

#include "matrix.h"

class Activation {
public:
    Activation() {}

    Matrix Activate(const Matrix& M) const;
    Matrix Derivative(const Matrix& M) const;

protected:
    // TODO: Add enum to allow multiple types of activation functions inside these func
    double ActivationFunction(double value) const;
    double DerivativeFunction(double value) const;

};