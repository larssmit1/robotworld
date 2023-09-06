#ifndef MAINSETTINGS_HPP_
#define MAINSETTINGS_HPP_

#include "Config.hpp"

enum RobotDriveMode {
	DEFAULT,
	KALMAN,
	PARTICLE
};

namespace Application
{

	/*
	 *
	 */
	class MainSettings
	{
		public:
			/**
			 *
			 */
			MainSettings();
			/**
			 *
			 */
			virtual ~MainSettings();
			/**
			 *
			 */
			bool getDrawOpenSet() const;
			/**
			 *
			 */
			bool getDrawLidar() const;
			/**
			 *
			 */
			RobotDriveMode getRobotDriveMode() const;
			/**
			 *
			 */
			void setDrawOpenSet( bool aDrawOpenSet);
			/**
			 * 
			 */
			void setDrawLidar( bool aDrawLidar);
			/**
			 * 
			 */
			void setRobotDriveMode( int aRobotDriveMode);
			/**
			 *
			 */
			unsigned long getSpeed() const;
			/**
			 *
			 */
			void setSpeed( unsigned long aSpeed);
			/**
			 *
			 */
			unsigned long getWorldNumber() const;
			/**
			 *
			 */
			void setWorldNumber( unsigned long aWorldNumber);

		private:
			bool drawOpenSet;
			bool drawLidar;
			unsigned long speed;
			unsigned long worldNumber;
			RobotDriveMode robotDriveMode;
	};

} /* namespace Application */

#endif /* SRC_MAINSETTINGS_HPP_ */
