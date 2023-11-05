#ifndef COMPASSSENSOR_HPP_
#define COMPASSSENSOR_HPP_

#include "Config.hpp"
#include "AbstractSensor.hpp"
#include "OrientationPercept.hpp"

namespace Model
{
	class Robot;
	typedef std::shared_ptr<Robot> RobotPtr;

	class CompassSensor : public AbstractSensor
	{
		public:
			/**
			 * @brief Construct a new Compass Sensor object
			 * 
			 * @param aRobot 
			 */
			explicit CompassSensor(Robot& aRobot);

			/**
			 * @brief Returns the angle in radians of the robot
			 * 
			 * @return std::shared_ptr<AbstractStimulus> 
			 */
			virtual std::shared_ptr<AbstractStimulus> getStimulus() const override;

			/**
			 * @brief Returns the orientation in degrees of the robot
			 * 
			 * @param anAbstractStimulus 
			 * @return std::shared_ptr<AbstractPercept> 
			 */
			virtual std::shared_ptr<AbstractPercept> getPerceptFor(std::shared_ptr<AbstractStimulus> anAbstractStimulus) const override;

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
			 * Standard deviation of the compass in degrees
			 */
			double stddev;
	};
} // namespace Model

#endif /* COMPASSSENSOR_HPP_ */