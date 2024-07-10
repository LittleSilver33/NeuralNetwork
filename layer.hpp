
#pragma once

#include "matrix.hpp"
#include "activation.hpp"

class Layer {

public:
    Layer() {}
    Layer(int nodesIn, int nodesOut);

    Matrix CalculateOutputs(const Matrix& inputs) const;
    void ApplyGradients(double learningRate);
    
protected:
    void RandomizeWeights();

protected:
    int nodesIn, nodesOut;
    Matrix weights, biases;
    Matrix weightsCostGradient, biasesCostGradient;
    Activation activation;
};