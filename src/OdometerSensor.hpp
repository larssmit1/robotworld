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
			explicit OdometerSensor(Robot& aRobot);
			virtual std::shared_ptr<AbstractStimulus> getStimulus() const override;
			virtual std::shared_ptr<AbstractPercept> getPerceptFor(std::shared_ptr<AbstractStimulus> anAbstractStimulus) const override;

			/**
			 * @brief Set the Std Dev object
			 * 
			 * @param aStdDev 
			 */
			static void setStdDev(double aStdDev){OdometerSensor::stddev = aStdDev;}

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
			/**
			 * random gen which is created initialy so the random numbers stay the same
			 */
			std::mt19937 gen;
	};
} // namespace Model

#endif /* ODOMETERSENSOR_HPP_ */