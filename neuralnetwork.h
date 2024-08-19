#pragma once

#include "layer.h"
#include "lossfunction.h"
#include "absl/status/status.h"

class NeuralNetwork {

public:
    NeuralNetwork(std::vector<int> layerSizes);

    void Learn(/* Insert Training Data Here */ double learningRate);

    Matrix CalculateOutputs(Matrix inputs) const;
    int Classify(Matrix inputs) const;

    absl::Status ReadNetwork(std::string &file_path);
    absl::Status SaveNetwork(std::string &file_path) const;

protected:
    std::vector<Layer> layers;
    std::vector<int> layerSizes;

    LossFunction lossFunction;
};
