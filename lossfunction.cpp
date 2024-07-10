
#include "lossfunction.hpp"

double LossFunction::Cost(const Matrix& predictedOutputs, const Matrix& expectedOutputs) const
{
    // cost is sum (for all x,y pairs) of: 0.5 * (x-y)^2
    
    Matrix error = predictedOutputs - expectedOutputs;
    error = error.ComponentwiseMul(error);
    return 0.5 * error.Sum();

    // double cost = 0;
    // for (int i = 0; i < predictedOutputs.Rows(); i++) {
    //     double error = predictedOutputs(i, 0) - expectedOutputs(i, 0);
    //     cost += error * error;
    // }

    // return 0.5 * cost;
}

double LossFunction::Derivative(double predictedOutput, double expectedOutput) const
{
    return predictedOutput - expectedOutput;
}