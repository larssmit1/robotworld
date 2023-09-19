#ifndef CONFIGREADER_HPP_
#define CONFIGREADER_HPP_

#include <string>
#include <vector>
#include <array>

#include "Widgets.hpp"

struct ConfigData{
    double stddevCompass = 0;
    double stddevOdometer = 0;
    double stddevLidar = 0;
    double beamAngleLidar = 0;
};

struct WorldConfigData{
    std::string name = "";
    wxPoint robot = wxPoint(0, 0);
    wxPoint goal = wxPoint(0, 0);
    std::vector<std::array<wxPoint, 2>> walls;
};

class ConfigReader {
    public:
        static ConfigData readConfig();
        static std::vector<WorldConfigData> readWorldConfig();
        static void printConfig(const ConfigData& cd);
        static void printWorldConfig(const WorldConfigData& wcd);
    private:
        static std::string configLocation;
        static std::string worldConfigLocation;

        static bool parseWall(const std::string& str, std::array<wxPoint, 2>& wall);
};

#endif /* CONFIGREADER_HPP_ */