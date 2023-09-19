#include "ConfigReader.hpp"

#include <fstream>
#include <sstream>
#include <iostream>

std::string ConfigReader::configLocation = "../config/config.txt";
std::string ConfigReader::worldConfigLocation = "../config/worldconfig.txt";

ConfigData ConfigReader::readConfig(){
    std::ifstream infile(configLocation);
    ConfigData cd;

    std::string line;
    while (std::getline(infile, line))
    {
        std::istringstream iss(line);
        std::string initialString;

        iss >> initialString;

        if(initialString == "stddev_compass:"){
            iss >> cd.stddevCompass;
        } else if(initialString == "stddev_odometer:"){
            iss >> cd.stddevOdometer;
        } else if(initialString == "stddev_lidar:"){
            iss >> cd.stddevLidar;
        } else if(initialString == "beamangle_lidar:"){
            iss >> cd.beamAngleLidar;
        }
    }

    return cd;
}

std::vector<WorldConfigData> ConfigReader::readWorldConfig(){
    std::ifstream infile(worldConfigLocation);
    std::vector<WorldConfigData> wcdVector;
    WorldConfigData wcd;

    bool checkWall = false;
    std::string line;
    while (std::getline(infile, line))
    {
        if(line == ""){ //TODO: needs to have whiteline at the end of file for now
            wcdVector.push_back(wcd);
            wcd = WorldConfigData(); // to empty the current configdata
            continue;
        }

        if(checkWall){
            if(line == "}"){
                checkWall = false;
            } else {
                std::array<wxPoint, 2> wall;
                if(parseWall(line, wall)){
                    wcd.walls.push_back(wall);
                }
            }
            continue;
        }

        std::istringstream iss(line);
        std::string initialString;
        iss >> initialString;

        if(initialString == "name:"){
            iss >> wcd.name;
        } else if(initialString == "robot:"){
            int x, y;
            char c;

            if(iss >> x >> c >> y){
                wcd.robot = wxPoint(x, y);
            }
        } else if(initialString == "goal:"){
            int x, y;
            char c;

            if(iss >> x >> c >> y){
                wcd.goal = wxPoint(x, y);
            }
        } else if(initialString == "walls{"){
            checkWall = true;
        }
    }

    return wcdVector;
}

void ConfigReader::printConfig(const ConfigData& cd){
    std::cout << "stddevCompass: " << cd.stddevCompass << std::endl
    << "stddevOdometer: " << cd.stddevOdometer << std::endl
    << "stddevLidar: " << cd.stddevLidar << std::endl << std::endl;
}

void ConfigReader::printWorldConfig(const WorldConfigData& wcd){
    std::cout << wcd.name << std::endl
    << wcd.robot.x << " " << wcd.robot.y << std::endl
    << wcd.goal.x << " " << wcd.goal.y << std::endl;

    for(std::array<wxPoint, 2> wall : wcd.walls){
        std::cout << "point1:" << wall[0].x << " " << wall[0].y
        << " point2:" << wall[1].x << " " << wall[1].y << std::endl;
    }
    std::cout << std::endl;
}

bool ConfigReader::parseWall(const std::string& str, std::array<wxPoint, 2>& wall){
    std::istringstream iss(str);
    int x, y;
    char c;
    wxPoint point1, point2;

    bool firstPointExists = false;
    bool secondPointExists = false;

    if(iss >> x >> c >> y){
        point1 = wxPoint(x, y);
        firstPointExists = true;
    }

    if(iss >> x >> c >> y){
        point2 = wxPoint(x, y);
        secondPointExists = true;
    }

    wall = {point1, point2};
    
    if(firstPointExists && secondPointExists){
        return true;
    } else {
        return false;
    }
}
