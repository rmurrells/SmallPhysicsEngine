#ifndef SIMPLEPARTICLEMODEL_HPP
#define SIMPLEPARTICLEMODEL_HPP

#include "ParticleContainer.hpp"

class SimpleParticleModel {
public:
  SimpleParticleModel(int const fps,
		      std::pair<int, int> const & boundary_position,
		      std::pair<int, int> const & boundary_size);
  void Run(ParticleContainer & particles);
private:
  void MoveParticles(ParticleContainer & particles);
  void UpdateParticleVelocity(Particle & particle1, Particle & particle2);
  void ParticleCollision(Particle & particle1, Particle & particle2);
  void ParticleCollisions(ParticleContainer & particles);
  void BoundaryCollision(Particle & particle);
  double move_factor;
  int boundary_x;
  int boundary_y;
  int boundary_w;
  int boundary_h;
};

#endif
