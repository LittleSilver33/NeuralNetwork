#include <gtest/gtest.h>
#include "neuralnetwork.h"
#include "build/feedforward.pb.h"
#include "absl/status/status.h"
#include <fstream>
#include <vector>
#include <string>

// Path to the test proto file
const std::string kTestFilePath = "test_network.pb";

// Helper function to compare vectors of doubles
void ExpectVectorsAreEqual(const std::vector<double>& actual, const std::vector<double>& expected) {
    ASSERT_EQ(actual.size(), expected.size()) << "Vectors are of different sizes.";
    for (size_t i = 0; i < actual.size(); ++i) {
        EXPECT_NEAR(actual[i], expected[i], 1e-9) << "Mismatch at index " << i;
    }
}

// Helper function to create a test proto file
void CreateTestProtoFile() {
    // Create a new neural network protobuf object
    neuralnetwork::NeuralNetwork nnProto;

    // Set layer sizes
    auto* layer_sizes = nnProto.mutable_layersizes();
    layer_sizes->Add(3);  // Example size for layer 1
    layer_sizes->Add(2);  // Example size for layer 2

    // Add layer 1
    auto* layer1 = nnProto.add_layers();
    layer1->set_nodesin(3);
    layer1->set_nodesout(2);

    // Set weights
    auto* weights = layer1->mutable_weights();
    weights->set_rows(2);
    weights->set_cols(3);
    weights->mutable_data()->Add(0.1);
    weights->mutable_data()->Add(0.2);
    weights->mutable_data()->Add(0.3);
    weights->mutable_data()->Add(0.4);
    weights->mutable_data()->Add(0.5);
    weights->mutable_data()->Add(0.6);

    // Set biases
    auto* biases = layer1->mutable_biases();
    biases->set_rows(2);
    biases->set_cols(1);
    biases->mutable_data()->Add(0.1);
    biases->mutable_data()->Add(0.2);

    // Set weight cost gradient
    auto* weight_cost_gradient = layer1->mutable_weightscostgradient();
    weight_cost_gradient->set_rows(2);
    weight_cost_gradient->set_cols(3);
    weight_cost_gradient->mutable_data()->Add(0.01);
    weight_cost_gradient->mutable_data()->Add(0.02);
    weight_cost_gradient->mutable_data()->Add(0.03);
    weight_cost_gradient->mutable_data()->Add(0.04);
    weight_cost_gradient->mutable_data()->Add(0.05);
    weight_cost_gradient->mutable_data()->Add(0.06);

    // Set biases cost gradient
    auto* bias_cost_gradient = layer1->mutable_biasescostgradient();
    bias_cost_gradient->set_rows(2);
    bias_cost_gradient->set_cols(1);
    bias_cost_gradient->mutable_data()->Add(0.01);
    bias_cost_gradient->mutable_data()->Add(0.02);

    // Set activation function
    layer1->set_activation("ReLU");  // Example activation function

    // Set loss function type
    nnProto.mutable_lossfunction()->set_type("MSE");  // Example loss function

    // Write to file
    std::ofstream ofs("test_model.proto", std::ios::binary);
    nnProto.SerializeToOstream(&ofs);
}

class NeuralNetworkTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Create the test proto file before each test
        CreateTestProtoFile();
    }

    void TearDown() override {
        // Clean up the test proto file after each test
        std::remove(kTestFilePath.c_str());
    }
};

TEST_F(NeuralNetworkTest, ReadNetwork_Success) {
    NeuralNetwork nn({3, 2, 1});  // Initialize with dummy sizes

    absl::Status status = nn.ReadNetwork(kTestFilePath);
    EXPECT_TRUE(status.ok()) << status.message();

    // Validate the loaded network
    const auto& layers = nn.GetLayers();
    const auto& layerSizes = nn.GetLayerSizes();
    const auto& lossFunction = nn.GetLossFunction();

    // Validate layer sizes
    ASSERT_EQ(layerSizes.size(), 3);
    EXPECT_EQ(layerSizes[0], 3);
    EXPECT_EQ(layerSizes[1], 2);
    EXPECT_EQ(layerSizes[2], 1);

    // Validate layer 1
    ASSERT_EQ(layers.size(), 2);
    const auto& layer1 = layers[0];
    EXPECT_EQ(layer1.nodesIn, 3);
    EXPECT_EQ(layer1.nodesOut, 2);

    std::vector<double> expectedWeights1 = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6};
    std::vector<double> expectedBiases1 = {0.1, 0.2};
    ExpectVectorsAreEqual(layer1.weights.data, expectedWeights1);
    ExpectVectorsAreEqual(layer1.biases.data, expectedBiases1);

    // Validate layer 2
    const auto& layer2 = layers[1];
    EXPECT_EQ(layer2.nodesIn, 2);
    EXPECT_EQ(layer2.nodesOut, 1);

    std::vector<double> expectedWeights2 = {0.7, 0.8};
    std::vector<double> expectedBiases2 = {0.4};
    ExpectVectorsAreEqual(layer2.weights.data, expectedWeights2);
    ExpectVectorsAreEqual(layer2.biases.data, expectedBiases2);

    // Validate loss function
    EXPECT_EQ(lossFunction.type, neuralnetwork::LossFunction::MEAN_SQUARED_ERROR);
}
