#include "OdometerSensor.hpp"

#include "Logger.hpp"
#include "Robot.hpp"
#include "RobotWorld.hpp"
#include "Wall.hpp"
#include "Shape2DUtils.hpp"
#include "MathUtils.hpp"
#include "MainApplication.hpp"

namespace Model
{
	OdometerSensor::OdometerSensor(Robot& aRobot) 
		: AbstractSensor(aRobot)
	{
		stddev = Application::MainApplication::getSettings().getConfiguration().stddevOdometer;

		std::random_device rd{};
		std::mt19937 aGen{rd()};
		gen = aGen;
	}

	std::shared_ptr<AbstractStimulus> OdometerSensor::getStimulus() const
	{
		Robot* robot = dynamic_cast<Robot*>(agent);

		std::mt19937 aGen = gen;
		std::normal_distribution<> noise{0, OdometerSensor::stddev};

		if(robot)
		{
			std::vector<wxPoint> points = robot->passedPoints;

			for(int i = 0; i < points.size(); i++)
			{
				points.at(i).x = points.at(i).x + noise(aGen);
				points.at(i).y = points.at(i).y + noise(aGen);
			}

			return std::make_shared<MileageStimulus>(points);
		}
		return std::make_shared<MileageStimulus>();
	}

	std::shared_ptr<AbstractPercept> OdometerSensor::getPerceptFor(std::shared_ptr<AbstractStimulus> anAbstractStimulus) const
	{
		MileageStimulus* stimulus = dynamic_cast<MileageStimulus*>(anAbstractStimulus.get());
		double totalDistance = 0;
		std::vector<double> stepDistances;

		if(stimulus->visitedPoints.size() > 1)
		{
			for(unsigned short i = 0; i < stimulus->visitedPoints.size() - 1; i++)
			{
				double xDiffSqr = std::pow(stimulus->visitedPoints.at(i + 1).x - stimulus->visitedPoints.at(i).x, 2);
				double yDiffSqr = std::pow(stimulus->visitedPoints.at(i + 1).y - stimulus->visitedPoints.at(i).y, 2);

				double pointDistance = std::sqrt(xDiffSqr + yDiffSqr);

				totalDistance += pointDistance;
				stepDistances.push_back(pointDistance);
			}
		}

		// Application::Logger::log(__PRETTY_FUNCTION__ +
		// 	std::string(": traveled ") + std::to_string(totalDistance) +
		// 	std::string(", steps ") + std::to_string(stepDistances.size()));

		return std::make_shared<MileagePercept>(totalDistance, stepDistances);
	}

	std::string OdometerSensor::asString() const
	{
		return "Odometer";
	}

	std::string OdometerSensor::asDebugString() const
	{
		return asString();
	}
} // namespace Model
