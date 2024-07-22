#include "neuralnetwork.h"
#include "build/feedforward.pb.h"
#include "absl/status/Status.h"

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

Status NeuralNetwork::SaveNetwork(const std::string &file_path)
{
    std::ifstream inputFile(file_path, std::ios::binary);
    if (!inputFile) {
        return absl::Status(absl::StatusCode::kInvalidArgument, "Failed to open the file at path: " + file_path);
    }

    std::string serializedData((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());

    NeuralNetwork nnProto;
    if (!nnProto.ParseFromString(serializedData)) {
        return absl::Status(absl::StatusCode::kInvalidArgument, "Failed to parse proto file");
    }

    layers.clear();
    layerSizes.clear();

    for (const auto& layerProto : nnProto.layers()) {
        Layer layer;
        layer.nodesIn = layerProto.nodesin();
        layer.nodesOut = layerProto.nodesout();

        layer.weights = { layerProto.weights().rows(), layerProto.weights().cols(),
                        { layerProto.weights().data().begin(), layerProto.weights().data().end() } };
        
        layer.biases = { layerProto.biases().rows(), layerProto.biases().cols(),
                        { layerProto.biases().data().begin(), layerProto.biases().data().end() } };

        layer.weightCostGradient = { layerProto.weightscostgradient().rows(), layersProto.weightscostgradient.cols(),
                                    { layerProto.weightscostgradient().data().begin(), layerProto.weightscostgradient().data().end() } };

        layer.activation = layerProto.activation();

        layers.push_back(layer);
    }

    layerSizes.assign(nnProto.layersizes().begin(), nnProto.layersizes().end());

    lossFunction.type = nnProto.lossfunction().type();

    return absl::Status(absl::StatusCode::kOk, "Model loaded successfully");
}
