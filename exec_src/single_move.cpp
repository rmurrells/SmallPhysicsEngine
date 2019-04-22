#include "Simulation.hpp"

int main() {
  Simulation simulation;
  double const width{800};
  double const height{600};
  double const vel_x{0}; double const vel_y{0};
  double const radius{4}; double const mass{1}; 
  int const n = 30;
  for(int i{1}; i < n; ++i) {
    for(int j{1}; j < n; ++j) {
      simulation.AddParticle(i*width/n, j*height/n, vel_x, vel_y, radius, mass);
    }
  }
  simulation.AddParticle(0, 0, 4, 3, radius, mass); 
  simulation.Run();
}
