#ifndef MILEAGEPERCEPT_HPP_
#define MILEAGEPERCEPT_HPP_

#include "Config.hpp"

#include "MileageStimulus.hpp"
#include "Point.hpp"

#include <limits>

namespace Model
{
	/**
	 *
	 */
	class MileagePercept : public AbstractPercept
	{
		public:
			/**
			 *
			 */
			explicit MileagePercept(double aTotalDistance, std::vector<double> aStepDistances)
				: totalDistance(aTotalDistance), stepDistances(aStepDistances)
			{
			}
			double totalDistance;
			std::vector<double> stepDistances;
			/**
			 * @name Debug functions
			 */
			//@{
			/**
			 * Returns a 1-line description of the object
			 */
			virtual std::string asString() const override
			{
				return "MileagePercept: " + std::to_string(totalDistance) + ", " + std::to_string(stepDistances.size());
			}
			/**
			 * Returns a description of the object with all data of the object usable for debugging
			 */
			virtual std::string asDebugString() const override
			{
				return asString();
			}
	}; //	class MileagePercept
} // namespace Model

#endif /* MILEAGEPERCEPT_HPP_ */
