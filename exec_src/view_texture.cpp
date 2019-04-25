#include "Simulation.hpp"

int main() {
  Simulation simulation;
  simulation.AddParticle(400, 300, 0, 0, 150, 1, {0, 0, 255, 255}, 10);
  simulation.Run();
}
