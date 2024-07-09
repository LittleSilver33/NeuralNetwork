
#pragma once

#include "layer.hpp"
#include "lossfunction.hpp"

class NeuralNetwork {

public:
    NeuralNetwork(std::vector<int> layerSizes);

    Matrix CalculateOutputs(Matrix inputs);
    int Classify(Matrix inputs);

protected:
    std::vector<Layer> layers;
    std::vector<int> layerSizes;

    LossFunction lossFunction;
};