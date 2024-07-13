
#pragma once

#include "matrix.h"

class LossFunction {

public:
    LossFunction() {}

    double Cost(const Matrix& predictedOutputs, const Matrix& expectedOutputs) const;
    double Derivative(double predictedOutput, double expectedOutput) const;

    // TODO: Add enum to allow multiple types of loss functions inside funcs

};