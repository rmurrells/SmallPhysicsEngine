#include "Simulation.hpp"

int main() {
  Simulation simulation;

  double const width{800};
  double const height{600};
  double const vel_x{2}; double const vel_y{2};
  double const radius{15}; double const mass{1};
  simulation.AddParticle(width/4, height/4, vel_x, vel_y, radius, mass);
  simulation.AddParticle(3*width/4, height/4, vel_x, vel_y, radius, mass);
  simulation.AddParticle(width/4, 3*height/4, vel_x, vel_y, radius, mass);
  simulation.AddParticle(3*width/4, 3*height/4, vel_x, vel_y, radius, mass);

  simulation.Run();
}
