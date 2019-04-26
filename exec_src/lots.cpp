#include "Simulation.hpp"

int main() {
  Simulation simulation;
  simulation.SetBackgroundColor(0, 0, 0);
  auto const [width, height] = simulation.GetWindowSize();
  double const radius{1}; double const mass{1}; 
  int const ni{100};
  int const nj{50};
  for(int i = 0; i < ni; ++i) {
    for(int j = 0; j < nj; ++j) {
      simulation.AddParticle(i*static_cast<double>(width)/ni, j*static_cast<double>(height)/nj,
			     0.5, 0.5, radius, mass, {0, 0, 255, 255});
    }
  }
  simulation.Run();
}
