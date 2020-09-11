#include "SimulationBuilder.hpp"

int main(int, char*[]) {
  Simulation simulation{SimulationBuilder().Build()};
  simulation.AddParticle(400, 300, 0, 0, 150, 1, {0, 0, 255, 255}, 9);
  simulation.Run();
  return 0;
}
