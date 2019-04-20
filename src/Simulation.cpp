#include "Simulation.hpp"

Simulation::Simulation() :
  sdl_window{"Simulation"}, sdl_renderer{sdl_window.GetWindowPtr()},
  fps_capper{sdl_window.GetRefreshRate()},
  particle_model{fps_capper.GetFPS(), {0, 0}, sdl_window.GetWindowSize()} {}

void Simulation::Run() {
  while(input_handler.Continue()) {
    particle_model.MoveParticles(particle_container);
    sdl_renderer.Render(particle_container);
    fps_capper.SleepToNextFrame();
  }
}
