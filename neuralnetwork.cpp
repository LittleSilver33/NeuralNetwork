
#include "neuralnetwork.hpp"

NeuralNetwork::NeuralNetwork(std::vector<int> layerSizes)
{
    layers = std::vector<Layer>(layerSizes.size() - 1);
    for (int i = 0; i < layers.size(); i++) {
        layers[i] = Layer(layerSizes[i], layerSizes[i + 1]);
    }
}

void NeuralNetwork::Learn(/* Insert Training Data Here */ double learningRate)
{
    // TODO: Implement
}

Matrix NeuralNetwork::CalculateOutputs(Matrix inputs) const
{
    for (Layer layer : layers) {
        inputs = layer.CalculateOutputs(inputs);
    }
    return inputs;
}

int NeuralNetwork::Classify(Matrix inputs) const
{
    Matrix outputs = CalculateOutputs(inputs);

    double maxOutput = outputs(0,0);
    int maxIndex = 0;
    for (int i = 0; i < outputs.Rows(); i++) {
        if (outputs(i, 0) > maxOutput) {
            maxOutput = outputs(i, 0);
            maxIndex = i;
        }
    }
    return maxIndex;
}