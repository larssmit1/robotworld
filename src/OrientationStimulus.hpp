#ifndef ORIENTATIONSTIMULUS_HPP_
#define ORIENTATIONSTIMULUS_HPP_

#include "Config.hpp"

#include "AbstractSensor.hpp"

namespace Model
{
	/**
	 *
	 */
	class OrientationStimulus : public AbstractStimulus
	{
		public:
			/**
			 * @brief Construct a new Orientation Stimulus object
			 * 
			 * @param aRadians 
			 */
			OrientationStimulus(double aRadians)
				:radians(aRadians)
			{}
			double radians;

			/**
			 * @brief Returns the object as a string
			 * 
			 * @return std::string 
			 */
			virtual std::string asString() const override
			{
				return "OrientationStimulus: " + std::to_string(radians);
			}

			/**
			 * @brief Returns the object as a string
			 * 
			 * @return std::string 
			 */
			virtual std::string asDebugString() const override
			{
				return asString();
			}
	}; // class OrientationStimulus
} // namespace Model

#endif /* ORIENTATIONSTIMULUS_HPP_ */
