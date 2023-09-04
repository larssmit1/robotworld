#ifndef KALMAN_HPP_
#define KALMAN_HPP_

#include "Matrix.hpp"

class Kalman {//kompas en odometer
    public:
        Kalman(double x, double y, double angle);
        virtual ~Kalman();

        void controlUpdate(const Matrix<double, 3, 1>& updateMatrix);
        void calculateKalmanGain();
        void measurementUpdate(const Matrix<double, 3, 1>& measurementVector);

    private:
        Matrix<double, 3, 1> processNoiseVector;
        Matrix<double, 3, 3> processNoiseCovarianceVector;
        Matrix<double, 3, 3> sensorCovarianceMatrix;

        Matrix<double, 3, 1> previousStateVector;
        Matrix<double, 3, 3> previousProcessCovariance;

        Matrix<double, 3, 1> predictedStateVector;
        Matrix<double, 3, 3> predictedProcessCovariance;
        double kalmanGain;
        Matrix<double, 3, 1> adjustedStateVector;
        Matrix<double, 3, 3> adjustedProcessCovariance;
};

#endif // KALMAN_HPP_