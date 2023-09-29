#include "ParticleFilter.hpp"

#include "Shape2DUtils.hpp"
#include "MathUtils.hpp"
#include "Logger.hpp"
#include "Wall.hpp"
#include "RobotWorld.hpp"
#include "MainApplication.hpp"

#include <random>
#include <cmath>

ParticleFilter::ParticleFilter(unsigned int aParticleCount, unsigned int aWorldWidth, unsigned int aWorldHeight, const wxPoint& startPosition)
: particleCount(aParticleCount), worldWidth(aWorldWidth), worldHeight(aWorldHeight), currentPosition(startPosition)
{
    addRandomParticles(particleCount);
}

ParticleFilter::~ParticleFilter(){}

void ParticleFilter::measurementUpdate(const Model::Stimuli& lidarValues){
    compareParticlesToLidar(lidarValues);
    calculateParticleChances();
    removeParticlesOnChance();
    determinePosition();
}

void ParticleFilter::actionUpdate(int xDiff, int yDiff){
    moveParticles(xDiff, yDiff);
    addRandomParticles(static_cast<unsigned int>(particleCount - particles.size()));
}

wxPoint ParticleFilter::getPosition() const {
    return currentPosition;
}

std::vector<Particle> ParticleFilter::getParticles() const {
    return particles;
}

void ParticleFilter::addRandomParticles(unsigned int aParticleCount){
    std::random_device rd{};
    std::mt19937 gen{rd()};
    std::uniform_int_distribution<int> dist(0 ,worldWidth * worldHeight - 1);

    for(unsigned int i = 0; i < aParticleCount; i++){
        int randomNmbr = dist(gen);
        int x = randomNmbr % worldWidth;
        int y = randomNmbr / worldWidth;
        particles.push_back(Particle{wxPoint(x, y), 0, 0});
    }
}

void ParticleFilter::compareParticlesToLidar(const Model::Stimuli& lidarValues){
    for(Particle& particle : particles){
        Model::Stimuli particleLidarValues = Model::LidarSensor::getLidarValueAtLocation(particle.location, 0);
        particle.comparisonValue = 0;

        for(unsigned int i = 0; i < lidarValues.size(); i++){
            if(particleLidarValues[i].angle == lidarValues[i].angle){
                particle.comparisonValue += sqrt(pow(lidarValues[i].distance - particleLidarValues[i].distance, 2));
            } else {
                Application::Logger::log("lidar values are for different angles, can't compare these.");
                particle.comparisonValue = -1;
                break;
            }
        }
    }
}

void ParticleFilter::removeParticlesOnChance(){
    std::random_device rd{};
    std::mt19937 gen{rd()};
    std::uniform_int_distribution<int> dist(0 ,100);

    for(int i = static_cast<int>(particles.size()) - 1; i >= 0 ; i--){ //loop through it backwards to prevent indexes from changing for future values
        int randomNmbr = dist(gen);

        if(particles[i].particleChance < randomNmbr){
            particles.erase(particles.begin() + i);
        }
    }
}

void ParticleFilter::calculateParticleChances(){
    double maxParticleDiff = Application::MainApplication::getSettings().getConfiguration().maxParticleDifference;
    double minimumChance = Application::MainApplication::getSettings().getConfiguration().minParticleChance;

    for(Particle& particle : particles){
        if(particle.comparisonValue < 0){
            particle.particleChance = 0;
        } else {
            if(particle.comparisonValue > maxParticleDiff){
                particle.comparisonValue = maxParticleDiff;
            }

            particle.particleChance = 100.0 - (particle.comparisonValue / maxParticleDiff * 100.0);

            if(particle.particleChance > 0){
                particle.particleChance += minimumChance;
            }
        }
    }
}

void ParticleFilter::moveParticles(int xDiff, int yDiff){
    for(Particle& particle : particles){
        particle.location.x += xDiff;
        particle.location.y += yDiff;
    }
}

void ParticleFilter::determinePosition(){
    int particleRange = Application::MainApplication::getSettings().getConfiguration().particleRange;
    std::vector<Particle> inRangeParticles;

    for(Particle particle : particles){
        if(particle.location.x - currentPosition.x < particleRange){
            if(particle.location.y - currentPosition.y < particleRange){
                inRangeParticles.push_back(particle);
            }
        }
    }

    Particle mostSimilarParticle;
    if(inRangeParticles.size() > 0){
        mostSimilarParticle = inRangeParticles[0];

        for(Particle& particle : inRangeParticles){
            if(particle.comparisonValue < mostSimilarParticle.comparisonValue){
                mostSimilarParticle = particle;
            }
        }
    } else {
        mostSimilarParticle = particles[0];

        for(Particle particle : particles){
            if(particle.comparisonValue < mostSimilarParticle.comparisonValue){
                mostSimilarParticle = particle;
            }
        }
    }

    currentPosition = mostSimilarParticle.location;
}

