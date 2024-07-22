#pragma once

#include "layer.h"
#include "lossfunction.h"
#include "absl/status/Status.h"

class NeuralNetwork {

public:
    NeuralNetwork(std::vector<int> layerSizes);

    void Learn(/* Insert Training Data Here */ double learningRate);

    Matrix CalculateOutputs(Matrix inputs) const;
    int Classify(Matrix inputs) const;

    Status SaveNetwork(std::string &file_path);

protected:
    std::vector<Layer> layers;
    std::vector<int> layerSizes;

    LossFunction lossFunction;
};
