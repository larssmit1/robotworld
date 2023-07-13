#include "CompassSensor.hpp"

#include "Logger.hpp"
#include "Robot.hpp"
#include "RobotWorld.hpp"
#include "Wall.hpp"
#include "Shape2DUtils.hpp"
#include "MathUtils.hpp"

#include <random>

#define PI 3.14159265359

namespace Model
{
	/* static */ double CompassSensor::stddev = 2;

	CompassSensor::CompassSensor(Robot& aRobot) 
		: AbstractSensor(aRobot)
	{}

	std::shared_ptr<AbstractStimulus> CompassSensor::getStimulus() const
	{
		Robot* robot = dynamic_cast<Robot*>(agent);
		if(robot)
		{
			std::random_device rd{};
			std::mt19937 gen{rd()};

			double stddev_radians = (stddev * PI) / 180;
		    std::normal_distribution<> noise{0, stddev_radians};

            double radians = Utils::Shape2DUtils::getAngle(robot->getFront()) + noise(gen);

			return std::make_shared<OrientationStimulus>(radians);
		}
		return std::make_shared<OrientationStimulus>(noAngle);
	}

	std::shared_ptr<AbstractPercept> CompassSensor::getPerceptFor(std::shared_ptr<AbstractStimulus> anAbstractStimulus) const
	{
		OrientationStimulus* distanceStimuli = dynamic_cast<OrientationStimulus*>(anAbstractStimulus.get());

		double degrees = (distanceStimuli->radians * 180) / PI;

		// Application::Logger::log(__PRETTY_FUNCTION__ +
		// 	std::string(": angle ") + std::to_string(degrees));

		return std::make_shared<OrientationPercept>(degrees);
	}

	std::string CompassSensor::asString() const
	{
		return "Compass";
	}

	std::string CompassSensor::asDebugString() const
	{
		return asString();
	}
} // namespace Model
