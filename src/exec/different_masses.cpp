#include "SimulationBuilder.hpp"

int main(int, char*[]) {
  Simulation simulation{SimulationBuilder()
			.SetBackgroundColor({0, 0, 0, 255})
			.Build()};
  double const height{static_cast<double>(simulation.GetWindowSize().second)};
  int const n{10};
  for(int i{1}; i < n; ++i) {
    simulation.AddParticle(200, i*height/n, 4, 0, 4, 1, {255/n, 255-255/n, 0, 255});
    simulation.AddParticle(500, i*height/n, 0, 0, 4, i, {static_cast<Uint8>(i*(255/n)), static_cast<Uint8>(255-i*(255/n)), 0, 255});
  }
  simulation.Run();
  return 0;
}
