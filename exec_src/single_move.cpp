#include "SimulationBuilder.hpp"

int main() {
  Simulation simulation{SimulationBuilder()
			.SetBackgroundColor({0, 0, 0, 255})
			.Build()};
  auto const [width, height] = simulation.GetWindowSize();
  double const vel_x{0}; double const vel_y{0};
  double const radius{4}; double const mass{1}; 
  int const nj = 30;
  int const ni = 34;
  for(int i{1}; i < ni; ++i) {
    for(int j{1}; j < nj; ++j) {
      simulation.AddParticle(i*static_cast<double>(width)/ni, j*static_cast<double>(height)/nj,
			     vel_x, vel_y, radius, mass, {0, 255, 0, 255});
    }
  }
  simulation.AddParticle(0, 0, 5, 4, 7, 20, {255, 0, 0, 255}); 
  simulation.Run();
}
