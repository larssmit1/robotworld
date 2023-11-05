#ifndef ODOMETERSENSOR_HPP_
#define ODOMETERSENSOR_HPP_

#include "Config.hpp"
#include "AbstractSensor.hpp"
#include "MileagePercept.hpp"

#include <random>

namespace Model
{
	class Robot;
	typedef std::shared_ptr<Robot> RobotPtr;

	class OdometerSensor : public AbstractSensor
	{
		public:
			/**
			 * @brief Construct a new Odometer Sensor object
			 * 
			 * @param aRobot 
			 */
			explicit OdometerSensor(Robot& aRobot);

			/**
			 * @brief Returns the points which the robot has passed
			 * 
			 * @return std::shared_ptr<AbstractStimulus> 
			 */
			virtual std::shared_ptr<AbstractStimulus> getStimulus() const override;

			/**
			 * @brief Returns the distance the robot has traveled
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
			 * Standard deviation of the odometer for each 10 pixels
			 */
			double stddev;
			/**
			 * random gen which is created initialy so the random numbers stay the same
			 */
			std::mt19937 gen;
	};
} // namespace Model

#endif /* ODOMETERSENSOR_HPP_ */