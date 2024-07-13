
#include "neuralnetwork.h"

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

void NeuralNetwork::SaveNetwork(std::string file_path) const
{
    std::ofstream file(file_path);
    if(!file.is_open())
    {
        std::cerr << "Error opening file " << file_path;
    }
    // Number of layers
    file << layerSizes.size(); << "\n";
    for(size_t i = 0; i < layers.size(); i++) {
        file << layerSizes[i] << " ";
    }
    std::vector<Layer> layers;
    std::vector<int> layerSizes;

    LossFunction lossFunction;
}
