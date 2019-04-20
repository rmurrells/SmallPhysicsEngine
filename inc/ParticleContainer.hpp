#ifndef PARTICLECONTAINER_HPP
#define PARTICLECONTAINER_HPP

#include <vector>
#include "Particle.hpp"

class ParticleContainer {
  using Container = std::vector<Particle>;
public:
  template<class... Args> void AddParticle(Args&&... args) {particles.emplace_back(std::forward<Args>(args)...);}
  Container& GetParticles() {return particles;}
  Container const& GetParticles() const {return particles;}
private:
  Container particles;
};

#endif
