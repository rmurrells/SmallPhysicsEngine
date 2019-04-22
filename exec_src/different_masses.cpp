#include "Simulation.hpp"

int main() {
  Simulation simulation;
  double const height{600};
  int const n{10};
  for(int i{1}; i < n; ++i) {
    simulation.AddParticle(200, i*height/n, 4, 0, 4, 1);
    simulation.AddParticle(500, i*height/n-2, 0, 0, 4, i);
  }
  simulation.Run();
}
