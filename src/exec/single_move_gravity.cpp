#include "SimulationBuilder.hpp"

int main(int, char*[]) {
  Simulation simulation{SimulationBuilder()
			.SetBackgroundColor({0, 0, 0, 255})
			.SetG(6.674)
			.SetBorderCR(0.5)
			.Build()};
  auto const [width, height] = simulation.GetWindowSize();
  simulation.AddParticle(width/2, height/2, 0, 0, 12, 20000, {255, 0, 0, 255});
  simulation.AddParticle(width/2, height/2-30, 3, 0, 7, 1, {255, 255, 0, 255}); 
  simulation.Run();
  return 0;
}
