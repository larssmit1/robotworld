#ifndef ORIENTATIONPERCEPT_HPP_
#define ORIENTATIONPERCEPT_HPP_

#include "Config.hpp"

#include "OrientationStimulus.hpp"

namespace Model
{
	/**
	 *
	 */
	class OrientationPercept : public AbstractPercept
	{
		public:
			/**
			 * @brief Construct a new Orientation Percept object
			 * 
			 * @param anOrientation 
			 */
			explicit OrientationPercept(double anOrientation) 
				:orientation(anOrientation)
			{}
			double orientation;

			/**
			 * @brief Returns the object as a string
			 * 
			 * @return std::string 
			 */
			virtual std::string asString() const override
			{
				return "OrientationPercept: " + std::to_string(orientation);
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
	}; //	class OrientationPercept
} // namespace Model

#endif /* ORIENTATIONPERCEPT_HPP_ */
