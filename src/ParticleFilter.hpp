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
        /**
         * @brief Construct a new Particle Filter object
         * 
         * @param aParticleCount The amount of particles the particle filter uses to determine the robots position
         * @param aWorldWidth The width of the world which the robot is driving in
         * @param aWorldHeight The height of the world which the robot is driving in
         * @param startPosition The start position of the robot
         */
        ParticleFilter(unsigned int aParticleCount, unsigned int aWorldWidth, unsigned int aWorldHeight, const wxPoint& startPosition);

        /**
         * @brief Destroy the Particle Filter object
         * 
         */
        ~ParticleFilter();

        /**
         * @brief Determines the position of the robot based on the lidar measurement and the particles
         * 
         * @param lidarValues 
         */
        void measurementUpdate(const Model::Stimuli& lidarValues);

        /**
         * @brief Moves the particles according to xDiff and yDiff and chooses new particles
         * 
         * @param xDiff 
         * @param yDiff 
         */
        void actionUpdate(int xDiff, int yDiff);

        /**
         * @brief Get the current position of the robot
         * 
         * @return wxPoint 
         */
        wxPoint getPosition() const;

        /**
         * @brief Get the particles which the algorithm is using
         * 
         * @return std::vector<Particle> 
         */
        std::vector<Particle> getParticles() const;
    private:
        unsigned int particleCount, worldWidth, worldHeight;
        std::vector<Particle> particles;
        wxPoint currentPosition;

        /**
         * @brief Adds a certain number of particles with random location to the particle vector
         * 
         * @param aParticleCount The amount of particles which are added
         */
        void addRandomParticles(unsigned int aParticleCount);

        /**
         * @brief Compares all particles in the particles vector with the lidar measurement
         * 
         * @param lidarValues The lidar measurement
         */
        void compareParticlesToLidar(const Model::Stimuli& lidarValues);

        /**
         * @brief Removes particles based on the chance they have to reappear
         * 
         */
        void removeParticlesOnChance();

        /**
         * @brief Calculates the chance for each particle to reappear
         * 
         */
        void calculateParticleChances();

        /**
         * @brief Moves all particles according to xDiff and yDiff
         * 
         * @param xDiff 
         * @param yDiff 
         */
        void moveParticles(int xDiff, int yDiff);

        /**
         * @brief Determines the current position of the robot based on the particles
         * 
         */
        void determinePosition();
};

#endif /* PARTICLEFILTER_HPP_ */