#ifndef SIMPLEPARTICLEMODEL_HPP
#define SIMPLEPARTICLEMODEL_HPP

#include "ParticleContainer.hpp"
#include "Border.hpp"

class SimpleParticleModel {
public:
  SimpleParticleModel(double const in_motion_damping_factor = 1,
		      double const in_coefficient_of_restitution = 1);
  void Run(ParticleContainer & particles) const;
private:
  void MoveParticles(ParticleContainer & particles) const;
  void HandleParticleSamePosition(Particle & particle1, Particle & particle2, double const radius_sum) const;
  void UpdateParticleVelocity(Particle & particle1, Particle & particle2) const;
  void CollideParticlePair(Particle & particle1, Particle & particle2) const;
  void ParticleCollisions(ParticleContainer & particles) const;
  double motion_damping_factor;
  double coefficient_of_restitution;
};

#endif
