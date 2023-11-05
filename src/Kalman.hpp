#ifndef KALMAN_HPP_
#define KALMAN_HPP_

#include "Matrix.hpp"

class Kalman {//kompas en odometer
    public:
        /**
         * @brief Construct a new Kalman object
         * 
         * @param x The initial x position of the robot
         * @param y The initial y position of the robot
         * @param angle The initial orientation of the robot
         */
        Kalman(double x, double y, double angle);

        /**
         * @brief Destroy the Kalman object
         * 
         */
        virtual ~Kalman();

        /**
         * @brief Predicts the state vector and process covariance using the updateMatrix
         * 
         * @param updateMatrix 
         */
        void controlUpdate(const Matrix<double, 3, 1>& updateMatrix);

        /**
         * @brief Calculates the kalman gain using the predicted state vector and the predicted process covariance
         * 
         */
        void calculateKalmanGain();

        /**
         * @brief Calculates the actual state vector using the predictions and measurementVector
         * 
         * @param measurementVector 
         */
        void measurementUpdate(const Matrix<double, 3, 1>& measurementVector);

        /**
         * @brief Get the State Vector object
         * 
         * @return Matrix<double, 3, 1> 
         */
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