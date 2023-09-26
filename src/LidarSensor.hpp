#ifndef LIDARSENSOR_HPP_
#define LIDARSENSOR_HPP_

#include "Config.hpp"
#include "AbstractSensor.hpp"
#include "DistancePercepts.hpp"

namespace Model
{
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
			 * @brief Returns the distance from the robot in all directions in which the beam collided
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
			 * @brief Returns the measurement of from lidar at a specific location
			 * 
			 * @param location The location at which it's measured
			 * @param noise noise added to the measurement to make it less accurate
			 * @return Stimuli 
			 */
			static Stimuli getLidarValueAtLocation(const wxPoint& location, double noise);

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
			 * Standard deviation of the lidar in pixels
			 */
			double stddev;
	};
} // namespace Model

#endif /* LIDARSENSOR_HPP_ */