#ifndef SIMPLEPARTICLECOLLIDER_HPP
#define SIMPLEPARTICLECOLLIDER_HPP

#include "ParticleContainer.hpp"
#include "ImmovableContainer.hpp"

class SimpleParticleCollider {
public:
  SimpleParticleCollider(double const in_coefficient_of_restitution = 1);
  void Collide(ParticleContainer & particles) const;
private:
  void MoveParticles(ParticleContainer & particles) const;
  void HandleParticleSamePosition(Particle & particle1, Particle & particle2) const;
  void UpdateParticleVelocity(Particle & particle1, Particle & particle2) const;
  void CollideParticlePair(Particle & particle1, Particle & particle2) const;
  double coefficient_of_restitution;
};

#endif
