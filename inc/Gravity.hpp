#ifndef GRAVITY_HPP
#define GRAVITY_HPP

#include "ParticleContainer.hpp"

class Gravity {
public:
  Gravity(double const in_G = 6.674);
  Gravity(Gravity const & copy_from) = default;
  double GetG() const;
  void LoopGravity(ParticleContainer& particles, double const framerate) const;
private:
  void Run(Particle& part1, Particle& part2, double const framerate) const;
  double G;
};
  
#endif
