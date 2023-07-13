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
			explicit CompassSensor(Robot& aRobot);
			virtual std::shared_ptr<AbstractStimulus> getStimulus() const override;
			virtual std::shared_ptr<AbstractPercept> getPerceptFor(std::shared_ptr<AbstractStimulus> anAbstractStimulus) const override;

			/**
			 * @brief Set the Std Dev object
			 * 
			 * @param aStdDev 
			 */
			static void setStdDev(double aStdDev){CompassSensor::stddev = aStdDev;}

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
			 * Standard deviation of the compass in degrees
			 */
			static double stddev;
	};
} // namespace Model

#endif /* COMPASSSENSOR_HPP_ */