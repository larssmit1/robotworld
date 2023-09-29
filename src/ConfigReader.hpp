#ifndef CONFIGREADER_HPP_
#define CONFIGREADER_HPP_

#include <string>
#include <vector>
#include <array>

#include "Widgets.hpp"

struct ConfigData{
    double stddevCompass = 0; // The stddev of the compass
    double stddevOdometer = 0; // The stddev of the odometer
    double stddevLidar = 0; // The stddev of the lidar
    double beamAngleLidar = 0; // The angle difference between the beams of the lidar
    int beamLengthLidar = 0; // The maximum beam length of the lidar
    int xSpacingRobot = 0; // Extra spacing which the robot will keep when determining a route width wise
    int ySpacingRobot = 0; // Extra spacing which the robot will keep when determining a route heigth wise
    double maxParticleDifference = 0; // The maximum deviation of the particle with the measurement to have a chance to reappear
    double minParticleChance = 0; // The minimum chance a particle which has a chance to reappear has to reappear
    int particleRange = 0; // The maximum distance between the previous position and the particles for them to be a possible position of the robot
};

struct WorldConfigData{
    std::string name = ""; // The name of the world
    wxPoint robot = wxPoint(0, 0); // The location of the robot in the world
    wxPoint goal = wxPoint(0, 0); // The location of the goal in the world
    std::vector<std::array<wxPoint, 2>> walls; //The locations of the walls in the world
};

class ConfigReader {
    public:
        /**
         * @brief Parses a config (in this case config.txt) to ConfigData and returns this
         * 
         * @return ConfigData 
         */
        static ConfigData readConfig();

        /**
         * @brief Parses a worldconfig (in this case worldconfig.txt) to WorldConfigData and returns this
         * 
         * @return std::vector<WorldConfigData> 
         */
        static std::vector<WorldConfigData> readWorldConfig();

        /**
         * @brief Prints a ConfigData object to cout
         * 
         * @param cd 
         */
        static void printConfig(const ConfigData& cd);

        /**
         * @brief Prints a WorldConfigData object to cout
         * 
         * @param wcd 
         */
        static void printWorldConfig(const WorldConfigData& wcd);
    private:
        static std::string configLocation; //The location of the config (in this case config.txt)
        static std::string worldConfigLocation; // The location of the worldconfig (in this case worldconfig.txt)

        /**
         * @brief Parses the two points of a wall from "str" and adds these to "wall" returning if this was succesfull
         * 
         * @param str The str from which the wall is parsed
         * @param wall The wall in which the points are added
         * @return true 
         * @return false 
         */
        static bool parseWall(const std::string& str, std::array<wxPoint, 2>& wall);
};

#endif /* CONFIGREADER_HPP_ */