#include "MainSettings.hpp"

namespace Application
{
	/**
	 *
	 */
	MainSettings::MainSettings() : drawOpenSet(true), drawLidar(false), speed(10), worldNumber(0), robotDriveMode(DEFAULT)
	{
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
	RobotDriveMode MainSettings::getRobotDriveMode() const
	{
		return robotDriveMode;
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
