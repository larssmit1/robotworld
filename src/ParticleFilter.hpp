#ifndef PARTICLEFILTER_HPP_
#define PARTICLEFILTER_HPP_

#include "Widgets.hpp"
#include "LidarSensor.hpp"

struct Particle{
    wxPoint location;
    double comparisonValue;
    double particleChance;
};

class ParticleFilter{
    public:
        ParticleFilter(unsigned int aParticleCount, unsigned int aWorldWidth, unsigned int aWorldHeight, const wxPoint& startPosition);
        ~ParticleFilter();

        void measurementUpdate(const Model::Stimuli& lidarValues);
        void actionUpdate(int xDiff, int yDiff);
        wxPoint getPosition() const;
        std::vector<Particle> getParticles() const;
    private:
        unsigned int particleCount, worldWidth, worldHeight;
        std::vector<Particle> particles;
        wxPoint currentPosition;

        void addRandomParticles(unsigned int aParticleCount);
        void compareParticlesToLidar(const Model::Stimuli& lidarValues);
        void removeParticlesOnChance();
        void calculateParticleChances();
        void moveParticles(int xDiff, int yDiff);
        void determinePosition();
};

#endif /* PARTICLEFILTER_HPP_ */