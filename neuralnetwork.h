
#pragma once

#include "layer.hpp"
#include "lossfunction.hpp"

class NeuralNetwork {

public:
    NeuralNetwork(std::vector<int> layerSizes);

    void Learn(/* Insert Training Data Here */ double learningRate);

    Matrix CalculateOutputs(Matrix inputs) const;
    int Classify(Matrix inputs) const;

protected:
    std::vector<Layer> layers;
    std::vector<int> layerSizes;

    LossFunction lossFunction;
};