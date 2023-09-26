#include "LidarSensor.hpp"

#include "Logger.hpp"
#include "Robot.hpp"
#include "RobotWorld.hpp"
#include "Wall.hpp"
#include "Shape2DUtils.hpp"
#include "MathUtils.hpp"
#include "MainApplication.hpp"

#include <random>

namespace Model
{
	LidarSensor::LidarSensor(Robot& aRobot) 
		: AbstractSensor(aRobot)
	{
		stddev = Application::MainApplication::getSettings().getConfiguration().stddevLidar;
	}

	std::shared_ptr<AbstractStimulus> LidarSensor::getStimulus() const
	{
		Robot* robot = dynamic_cast<Robot*>(agent);
		if(robot)
		{
			std::random_device rd{};
			std::mt19937 gen{rd()};
		    std::normal_distribution<> noise{0, LidarSensor::stddev};

			Stimuli measurements = getLidarValueAtLocation(robot->getPosition(), noise(gen));

			return std::make_shared<DistanceStimuli>(measurements);
		}
		return std::make_shared<DistanceStimuli>();
	}

	std::shared_ptr<AbstractPercept> LidarSensor::getPerceptFor(std::shared_ptr<AbstractStimulus> anAbstractStimulus) const
	{
		Robot* robot = dynamic_cast<Robot*>(agent);
		if (robot)
		{
			wxPoint robotLocation = robot->getPosition();

			DistanceStimuli* distanceStimuli = dynamic_cast<DistanceStimuli*>(anAbstractStimulus.get());
			PointCloud pointcloud;

			for(DistanceStimulus distanceStimulus : distanceStimuli->stimuli)
			{
				wxPoint endpoint{static_cast<int>(robotLocation.x + std::cos(distanceStimulus.angle) * distanceStimulus.distance),
								static_cast<int>(robotLocation.y + std::sin(distanceStimulus.angle) * distanceStimulus.distance)};

				pointcloud.push_back(DistancePercept(endpoint));
			}
			return std::make_shared<DistancePercepts>(pointcloud, distanceStimuli->stimuli);
		}
		return std::make_shared<DistancePercepts>();
	}

	Stimuli LidarSensor::getLidarValueAtLocation(const wxPoint& location, double noise)
	{
		int beamLength = Application::MainApplication::getSettings().getConfiguration().beamLengthLidar;
    	double beamAngle = Application::MainApplication::getSettings().getConfiguration().beamAngleLidar;

		Stimuli measurements;

		for(int i = 0; i <= 360 / beamAngle; i++)
		{
			double angle = (beamAngle * i * Utils::PI) / 180;
			double distance = beamLength;

			std::vector<WallPtr> walls = RobotWorld::getRobotWorld().getWalls();
			for (std::shared_ptr<Wall> wall : walls)
			{
				wxPoint wallPoint1 = wall->getPoint1();
				wxPoint wallPoint2 = wall->getPoint2();
				wxPoint laserEndpoint{static_cast<int>(location.x + std::cos(angle) * beamLength + noise),
									static_cast<int>(location.y + std::sin(angle) * beamLength + noise)};

				wxPoint interSection = Utils::Shape2DUtils::getIntersection(wallPoint1, wallPoint2, location, laserEndpoint);

				if(interSection != wxDefaultPosition)
				{
					double new_distance = Utils::Shape2DUtils::distance(location, interSection);
					
					if(new_distance < distance)
					{
						distance = new_distance;
					}
				}
			}

			measurements.push_back(DistanceStimulus(angle, distance));
			// Application::Logger::log(__PRETTY_FUNCTION__ +
			// 						std::string(": angle ") + std::to_string(beamAngle * i) +
			// 						std::string(", distance ") + std::to_string(distance));

		}
		return measurements;
	}

	std::string LidarSensor::asString() const
	{
		return "Lidar";
	}

	std::string LidarSensor::asDebugString() const
	{
		return asString();
	}
} // namespace Model
