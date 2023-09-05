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

        Matrix<double, 3, 1> getStateVector();

    private:
        Matrix<double, 3, 1> processNoiseVector;
        Matrix<double, 3, 3> processNoiseCovarianceVector;
        Matrix<double, 3, 3> sensorCovarianceMatrix;

        Matrix<double, 3, 1> stateVector;
        Matrix<double, 3, 3> processCovariance;

        Matrix<double, 3, 1> predictedStateVector;
        Matrix<double, 3, 3> predictedProcessCovariance;
        double kalmanGain;
};

#endif // KALMAN_HPP_