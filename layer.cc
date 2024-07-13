
#include "layer.h"

#include <math.h>
#include <random>

Layer::Layer(int nodesIn, int nodesOut)
{
	this->nodesIn = nodesIn;
	this->nodesOut = nodesOut;
	this->weights = Matrix(nodesIn, nodesOut);
	this->biases = Matrix(nodesOut);
	this->weightsCostGradient = Matrix(nodesIn * nodesOut);
    this->biasesCostGradient = Matrix(nodesOut);
	this->activation = Activation();

	RandomizeWeights();
}

Matrix Layer::CalculateOutputs(const Matrix& inputs) const
{
    Matrix weightedInputs = (weights * inputs) + biases;
    Matrix activations = activation.Activate(weightedInputs);
    return activations;
}

void Layer::ApplyGradients(double learningRate)
{
	for (int nodeOut = 0; nodeOut < nodesOut; nodeOut++) {
		biases(nodeOut, 0) -= biasesCostGradient(nodeOut, 0) * learningRate;
		for (int nodeIn = 0; nodeIn < nodesIn; nodeIn++) {
			weights(nodeIn, nodeOut) = weightsCostGradient(nodeIn, nodeOut) * learningRate;
		}
	}
}

void Layer::RandomizeWeights()
{
	// Random Number Generator
	std::random_device rd;
	std::mt19937 rng(rd());
	std::normal_distribution<> dist(0.0, 1.0);

	double pi = 2 * acos(0.0);
	for (int r = 0; r < weights.Rows(); r++) {
		for (int c = 0; c < weights.Columns(); c++) {
			double x1 = 1.0 - dist(rng);
			double x2 = 1.0 - dist(rng);

			double y1 = std::sqrt(-2.0 * std::log(x1)) * std::cos(2.0 * pi * x2);
			weights(r, c) = y1 / std::sqrt(nodesIn);
		}
	}
}
