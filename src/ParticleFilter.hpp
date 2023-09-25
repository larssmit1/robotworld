#ifndef PARTICLEFILTER_HPP_
#define PARTICLEFILTER_HPP_

#include "Widgets.hpp"
#include "LidarSensor.hpp"

class ParticleFilter{
    public:
        ParticleFilter(unsigned int aParticleCount, unsigned int aWorldWidth, unsigned int aWorldHeight);
        ~ParticleFilter();
        void compareParticlesToLidar(const Model::Stimuli& lidarValues);
    private:
        unsigned int particleCount, worldWidth, worldHeight;
        std::vector<wxPoint> particles;
        std::vector<double> comparisonValues;

        void addRandomParticles(unsigned int aParticleCount);
};

#endif /* PARTICLEFILTER_HPP_ */