#ifndef MAINSETTINGS_HPP_
#define MAINSETTINGS_HPP_

#include "Config.hpp"
#include "ConfigReader.hpp"

enum RobotDriveMode {
	DEFAULT,
	KALMAN
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
			ConfigData getConfiguration() const;
			/**
			 *
			 */
			std::vector<WorldConfigData> getWorldConfigurations() const;
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
			/**
			 * 
			 */
			void setRobotDriveMode( int aRobotDriveMode);

		private:
			bool drawOpenSet;
			bool drawLidar;
			unsigned long speed;
			unsigned long worldNumber;
			RobotDriveMode robotDriveMode;
			ConfigData configuration;
			std::vector<WorldConfigData> worldConfigurations;
	};

} /* namespace Application */

#endif /* SRC_MAINSETTINGS_HPP_ */
