
#pragma once

#include "matrix.hpp"
#include "activation.hpp"

class Layer {

public:
    Layer() {}
    Layer(int nodesIn, int nodesOut);

    Matrix CalculateOutputs(const Matrix& inputs);

protected:
    int nodesIn, nodesOut;
    Matrix weights;
    Matrix biases;

    Activation activation;
};