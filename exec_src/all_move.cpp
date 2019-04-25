#include "Simulation.hpp"

int main() {
  Simulation simulation;
  double const width{800};
  double const height{600};
  double const vel_x{1}; double const vel_y{1};
  double const radius{4}; double const mass{1}; 
  int const n = 30;
  Uint32 color{0}; Uint32 const inc{(1 << 24)/(n*n)};
  for(int j{1}; j < n; ++j) {
    for(int i{1}; i < n; ++i) {
      simulation.AddParticle(i*width/n, j*height/n, vel_x, vel_y, radius, mass, color += inc, 21);
    }
  }
  simulation.Run();
}
