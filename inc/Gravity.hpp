#ifndef GRAVITY_HPP
#define GRAVITY_HPP
#include "ParticleContainer.hpp"

void Gravity(Particle& part1, Particle& part2, double framerate);
void LoopGravity(ParticleContainer& particles, double framerate);

#endif
