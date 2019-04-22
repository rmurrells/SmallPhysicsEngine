#include "Simulation.hpp"

Simulation::Simulation() :
  sdl_window{"Simulation"}, sdl_renderer{sdl_window.GetWindowPtr()},
  fps_capper{60} {}

void Simulation::Run() {
  Border border{{0, 0}, sdl_window.GetWindowSize()};
  while(input_handler.Continue()) {
    SimpleParticleModel::Run(particles, border);
    sdl_renderer.Render(particles);
    fps_capper.SleepToNextFrame();
  }
}
