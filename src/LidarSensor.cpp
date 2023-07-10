#include "LidarSensor.hpp"

#include "Logger.hpp"
#include "Robot.hpp"
#include "RobotWorld.hpp"
#include "Wall.hpp"
#include "Shape2DUtils.hpp"
#include "MathUtils.hpp"

#include <random>

namespace Model
{
	/* static */ double LidarSensor::stddev = 10.0;
	/* static */ double LidarSensor::beamAngle = 2;

	LidarSensor::LidarSensor(Robot& aRobot) 
		: AbstractSensor(aRobot)
	{}

	std::shared_ptr<AbstractStimulus> LidarSensor::getStimulus() const
	{
		Robot* robot = dynamic_cast<Robot*>(agent);
		if(robot)
		{
			std::random_device rd{};
			std::mt19937 gen{rd()};
		    std::normal_distribution<> noise{0, LidarSensor::stddev};

			Stimuli measurements;

			for(int i = 0; i <= 360 / beamAngle; i++)
			{
				double angle = beamAngle * i;
				double distance = -1;

				std::vector<WallPtr> walls = RobotWorld::getRobotWorld().getWalls();
				for (std::shared_ptr<Wall> wall : walls)
				{
					wxPoint wallPoint1 = wall->getPoint1();
					wxPoint wallPoint2 = wall->getPoint2();
					wxPoint robotLocation = robot->getPosition();
					wxPoint laserEndpoint{static_cast<int>(robotLocation.x + std::cos(angle) * lidarBeamLength + noise(gen)),
										static_cast<int>(robotLocation.y + std::sin(angle) * lidarBeamLength + noise(gen))};

					wxPoint interSection = Utils::Shape2DUtils::getIntersection(wallPoint1, wallPoint2, robotLocation, laserEndpoint);

					if(interSection != wxDefaultPosition)
					{
						double new_distance = Utils::Shape2DUtils::distance(robotLocation, interSection);
						if(new_distance > distance)
						{
							distance = new_distance;
						}
					}
				}

				if(distance != -1)
				{
					measurements.push_back(DistanceStimulus(angle, distance));
					// Application::Logger::log(__PRETTY_FUNCTION__ +
					// 						std::string(": angle ") + std::to_string(angle) +
					// 						std::string(", distance ") + std::to_string(distance));
				}
			}
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
			return std::make_shared<DistancePercepts>(pointcloud);
		}
		return std::make_shared<DistancePercepts>();
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
