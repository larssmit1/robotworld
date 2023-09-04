#include "Kalman.hpp"
#include <cmath>

Kalman::Kalman(double x, double y, double angle)
{
    Matrix<double, 3, 1> aStateVector{x, y, angle};
    Matrix<double, 3, 3> aCovarianceMatrix;

    Matrix<double, 3, 1> aProcessNoiseVector(0);
    Matrix<double, 3, 3> aProcessNoiseCovarianceVector(0);
    Matrix<double, 3, 3> aSensorCovarianceMatrix;

    previousStateVector = aStateVector;
    previousProcessCovariance = aCovarianceMatrix.identity();

    processNoiseVector = aProcessNoiseVector;
    processNoiseCovarianceVector = aProcessNoiseCovarianceVector;
    sensorCovarianceMatrix = aSensorCovarianceMatrix.identity();
}

Kalman::~Kalman()
{
    //nothing
}

void Kalman::controlUpdate(const Matrix<double, 3, 1>& updateMatrix)
{
    double timeDiff = 1; //timeDiff is simply 1 because we work in steps
    Matrix<double, 3, 3> matrixA;
    Matrix<double, 3, 3> matrixB;

    matrixA = matrixA.identity();
    matrixB = matrixB.identity();

    predictedStateVector = matrixA * previousStateVector + matrixB * updateMatrix + processNoiseVector;
    predictedProcessCovariance = matrixA * previousProcessCovariance * matrixA.transpose() + processNoiseCovarianceVector;
}

void Kalman::calculateKalmanGain()
{
    kalmanGain = (predictedProcessCovariance * (predictedProcessCovariance + sensorCovarianceMatrix).inverse()).at(0,0);
}

void Kalman::measurementUpdate(const Matrix<double, 3, 1>& measurementVector)
{
    adjustedStateVector = predictedStateVector + (measurementVector - predictedStateVector) * kalmanGain;
    adjustedProcessCovariance = (predictedProcessCovariance.identity() - predictedProcessCovariance.identity() * kalmanGain) * predictedProcessCovariance;
}
