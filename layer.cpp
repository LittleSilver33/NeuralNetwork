
#include "layer.hpp"

Layer::Layer(int nodesIn, int nodesOut)
{
	this->nodesIn = nodesIn;
	this->nodesOut = nodesOut;
	this->weights = Matrix(nodesIn, nodesOut);
	this->biases = Matrix(nodesOut);
	this->activation = Activation();
}

Matrix Layer::CalculateOutputs(const Matrix& inputs)
{
    Matrix weightedInputs = (weights * inputs) + biases;
    Matrix activations = activation.Activate(weightedInputs);
    return activations;
}
