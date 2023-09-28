#include "MainSettings.hpp"

namespace Application
{
	/**
	 *
	 */
	MainSettings::MainSettings() : drawOpenSet(true), drawLidar(false), speed(10), worldNumber(0), robotDriveMode(DEFAULT)
	{
		configuration = ConfigReader::readConfig();
		worldConfigurations = ConfigReader::readWorldConfig();

		ConfigReader::printConfig(configuration);
		for(WorldConfigData wcd : worldConfigurations){
			ConfigReader::printWorldConfig(wcd);
		}
	}
	/**
	 *
	 */
	MainSettings::~MainSettings()
	{
	}
	/**
	 *
	 */
	bool MainSettings::getDrawOpenSet() const
	{
		return drawOpenSet;
	}
	/**
	 *
	 */
	bool MainSettings::getDrawLidar() const
	{
		return drawLidar;
	}
	/**
	 *
	 */
	bool MainSettings::getDrawParticles() const
	{
		return drawParticles;
	}
	/**
	 *
	 */
	bool MainSettings::getDrawKalmanRoute() const
	{
		return drawKalmanRoute;
	}
	/**
	 *
	 */
	bool MainSettings::getDrawParticleFilterRoute() const
	{
		return drawParticleFilterRoute;
	}
	/**
	 *
	 */
	RobotDriveMode MainSettings::getRobotDriveMode() const
	{
		return robotDriveMode;
	}
	/**
	 *
	 */
	ConfigData MainSettings::getConfiguration() const
	{
		return configuration;
	}
	/**
	 *
	 */
	std::vector<WorldConfigData> MainSettings::getWorldConfigurations() const
	{
		return worldConfigurations;
	}
	/**
	 *
	 */
	void MainSettings::setDrawOpenSet( bool aDrawOpenSet)
	{
		drawOpenSet = aDrawOpenSet;
	}
	/**
	 *
	 */
	void MainSettings::setDrawParticles( bool aDrawParticles)
	{
		drawParticles = aDrawParticles;
	}
	/**
	 *
	 */
	void MainSettings::setDrawKalmanRoute( bool aDrawKalmanRoute)
	{
		drawKalmanRoute = aDrawKalmanRoute;
	}
	/**
	 *
	 */
	void MainSettings::setDrawParticleFilterRoute( bool aDrawParticleFilterRoute)
	{
		drawParticleFilterRoute = aDrawParticleFilterRoute;
	}
	/**
	 *
	 */
	void MainSettings::setDrawLidar( bool aDrawLidar)
	{
		drawLidar = aDrawLidar;
	}
	/**
	 *
	 */
	void MainSettings::setRobotDriveMode( int aRobotDriveMode)
	{
		if(aRobotDriveMode >= 0 && aRobotDriveMode < 3){ // 0 = DEFAULT, 1 = KALMAN, 2 = PARTICLE
			robotDriveMode = (RobotDriveMode) aRobotDriveMode;
		} else {
			robotDriveMode = DEFAULT;
		}
	}
	/**
	 *
	 */
	unsigned long MainSettings::getSpeed() const
	{
		return speed;
	}
	/**
	 *
	 */
	void MainSettings::setSpeed( unsigned long aSpeed)
	{
		speed = aSpeed;
	}
	/**
	 *
	 */
	unsigned long MainSettings::getWorldNumber() const
	{
		return worldNumber;
	}
	/**
	 *
	 */
	void MainSettings::setWorldNumber( unsigned long aWorldNumber)
	{
		worldNumber = aWorldNumber;
	}
} /* namespace Application */
