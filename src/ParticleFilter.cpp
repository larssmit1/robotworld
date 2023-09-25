#include "ParticleFilter.hpp"

#include "Shape2DUtils.hpp"
#include "MathUtils.hpp"
#include "Wall.hpp"
#include "RobotWorld.hpp"
#include "MainApplication.hpp"

#include <random>
#include <iostream>
#include <cmath>

ParticleFilter::ParticleFilter(unsigned int aParticleCount, unsigned int aWorldWidth, unsigned int aWorldHeight)
: particleCount(aParticleCount), worldWidth(aWorldWidth), worldHeight(aWorldHeight)
{
    addRandomParticles(particleCount);
}

ParticleFilter::~ParticleFilter(){}

void ParticleFilter::addRandomParticles(unsigned int aParticleCount){
    std::random_device rd{};
    std::mt19937 gen{rd()};
    std::uniform_int_distribution<int> dist(0 ,worldWidth * worldHeight - 1);

    for(unsigned int i = 0; i < aParticleCount; i++){
        int randomNmbr = dist(gen);
        int x = randomNmbr % worldWidth;
        int y = randomNmbr / worldWidth;
        particles.push_back(wxPoint(x, y));
    }
}

void ParticleFilter::compareParticlesToLidar(const Model::Stimuli& lidarValues){
    for(wxPoint particle : particles){
        Model::Stimuli particleLidarValues = Model::LidarSensor::getLidarValueAtLocation(particle, 0);
        double comparisonValue = 0;

        for(unsigned int i = 0; i < particleLidarValues.size(); i++){
            if(particleLidarValues[i].angle == lidarValues[i].angle){
                comparisonValue += sqrt(pow(lidarValues[i].distance - particleLidarValues[i].distance, 2));
            } else {
                std::cout << "lidar values are for different angles, can't compare these." << std::endl;
                return;
            }
        }

        std::cout << "comparison value: " << comparisonValue << std::endl;
    }
}
