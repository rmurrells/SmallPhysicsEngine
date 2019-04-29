#ifndef PARTICLEMOVER_HPP
#define PARTICLEMOVER_HPP

#include "ParticleContainer.hpp"

class ParticleMover {
public:
  ParticleMover(double const motion_damping_factor = 1);
  void Move(ParticleContainer & particles) const;
private:
  double motion_damping_factor;
};

#endif
