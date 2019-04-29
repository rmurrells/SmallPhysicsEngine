#include "ParticleMover.hpp"

ParticleMover::ParticleMover(double const in_motion_damping_factor) :
  motion_damping_factor{in_motion_damping_factor} {}

void ParticleMover::Move(ParticleContainer & particles) const {
  for(Particle & particle : particles) {
    particle.vel_x *= motion_damping_factor;
    particle.vel_y *= motion_damping_factor;
    particle.pos_x += particle.vel_x;
    particle.pos_y += particle.vel_y;
  }
}

