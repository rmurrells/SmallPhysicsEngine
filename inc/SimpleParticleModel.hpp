#ifndef SIMPLEPARTICLEMODEL_HPP
#define SIMPLEPARTICLEMODEL_HPP

#include "ParticleContainer.hpp"

class SimpleParticleModel {
public:
  SimpleParticleModel(int const fps,
		      std::pair<int, int> const & boundary_position,
		      std::pair<int, int> const & boundary_size);
  void MoveParticles(ParticleContainer & particle_container);
private:
  void BoundaryCollision(Particle & particle);
  double move_factor;
  int boundary_x;
  int boundary_y;
  int boundary_w;
  int boundary_h;
};

#endif
