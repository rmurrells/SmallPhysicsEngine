#include "Simulation.hpp"

int main() {
  Simulation simulation;
  double const width{800};
  double const height{600};
  double const vel_x{2}; double const vel_y{2};
  double const mass{1}; double const radius{3};
  simulation.AddParticle(300, 200, vel_x, 0, mass, radius);
  simulation.AddParticle(500, 200, -vel_x, 0, mass, radius);
  int const n = 50;
  for(int i{1}; i <= n; ++i) {
    for(int j{1}; j <= n; ++j) {
      simulation.AddParticle(i*width/n, j*height/n, vel_x, vel_y, mass, radius);
    }
  }
  simulation.Run();
}
