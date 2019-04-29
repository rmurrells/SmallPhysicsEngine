#ifndef IMMOVABLEPARTICLECOLLIDER_HPP
#define IMMOVABLEPARTICLECOLLIDER_HPP

#include "ParticleContainer.hpp"
#include "ImmovableContainer.hpp"

class ImmovableParticleCollider {
public:
  ImmovableParticleCollider(double const in_coefficient_of_restitution = 1);
  void Collide(ParticleContainer & particles, ImmovableContainer const & immovables) const;
private:
  void UpdateParticleVelocity(Particle & particle, Immovable const & immovable) const;
  void HandleParticleSamePosition(Particle & particle,
				  Immovable const & immovable) const;
  void CollideParticleWImmovable(Particle & particle,
				 Immovable const & immovable) const;
  void ImmovableCollisions(ParticleContainer & particles,
			   ImmovableContainer const & immovables) const;
  double coefficient_of_restitution;
};

#endif
