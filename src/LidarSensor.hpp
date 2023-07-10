#ifndef LIDARSENSOR_HPP_
#define LIDARSENSOR_HPP_

#include "Config.hpp"
#include "AbstractSensor.hpp"
#include "DistancePercepts.hpp"

namespace Model
{
	/**
	 * Compile time configurable length of the laser beam
	 */
	const short int lidarBeamLength = 1024;

	class Robot;
	typedef std::shared_ptr<Robot> RobotPtr;

	class LidarSensor : public AbstractSensor
	{
		public:
			/**
			 * @brief Construct a new Lidar Sensor object
			 * 
			 * @param aRobot The robot to whitch the lidar is connected
			 */
			explicit LidarSensor(Robot& aRobot);

			/**
			 * @brief Returns the distance from the robot in all directions
			 * 
			 * @return std::shared_ptr<AbstractStimulus> 
			 */
			virtual std::shared_ptr<AbstractStimulus> getStimulus() const override;

			/**
			 * @brief Returns the points where the lidar stopped
			 * 
			 * @param anAbstractStimulus 
			 * @return std::shared_ptr<AbstractPercept> 
			 */
			virtual std::shared_ptr<AbstractPercept> getPerceptFor(std::shared_ptr<AbstractStimulus> anAbstractStimulus) const override;

			/**
			 * @brief Set the Std Dev object
			 * 
			 * @param aStdDev 
			 */
			static void setStdDev(double aStdDev){LidarSensor::stddev = aStdDev;}

			/**
			 * @brief Get the Std Dev object
			 * 
			 * @return double 
			 */
			static double getStdDev(){return stddev;}

			/**
			 * @brief Returns a string which describes the object
			 * 
			 * @return std::string 
			 */
			virtual std::string asString() const override;

			/**
			 * @brief Returns a string which describes the object
			 * 
			 * @return std::string 
			 */
			virtual std::string asDebugString() const override;
		protected:
		private:
			/**
			 * Standard deviation of the odometer per 10 pixels
			 */
			static double stddev;
			static double beamAngle;
	};
} // namespace Model

#endif /* LIDARSENSOR_HPP_ */