#ifndef MILEAGESTIMULUS_HPP_
#define MILEAGESTIMULUS_HPP_

#include "Config.hpp"

#include "AbstractSensor.hpp"
#include "Point.hpp"

#include <limits>

namespace Model
{
	/**
	 *
	 */
	class MileageStimulus : public AbstractStimulus
	{
		public:
			/**
			 *
			 */
			MileageStimulus() = default;
			/**
			 *
			 */
			MileageStimulus(const std::vector<wxPoint>& aVisitedPoints) 
				: visitedPoints(aVisitedPoints)
			{
			};
			std::vector<wxPoint> visitedPoints;
			/**
			 * @name Debug functions
			 */
			//@{
			/**
			 * Returns a 1-line description of the object
			 */
			virtual std::string asString() const override
			{
				return "MileageStimulus: " + std::to_string(visitedPoints.size());
			}
			/**
			 * Returns a description of the object with all data of the object usable for debugging
			 */
			virtual std::string asDebugString() const override
			{
				return asString();
			}
	}; // class MileageStimulus
} // namespace Model

#endif /* MILEAGESTIMULUS_HPP_ */
