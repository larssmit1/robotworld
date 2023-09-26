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
        ParticleFilter(unsigned int aParticleCount, unsigned int aWorldWidth, unsigned int aWorldHeight);
        ~ParticleFilter();

        void measurementUpdate(const Model::Stimuli& lidarValues);
        void actionUpdate(int xDiff, int yDiff);
        std::vector<Particle> getParticles() const;
    private:
        unsigned int particleCount, worldWidth, worldHeight;
        std::vector<Particle> particles;

        void addRandomParticles(unsigned int aParticleCount);
        void compareParticlesToLidar(const Model::Stimuli& lidarValues);
        void removeParticlesOnChance();
        void calculateParticleChances();
        void moveParticles(int xDiff, int yDiff);
};

#endif /* PARTICLEFILTER_HPP_ */