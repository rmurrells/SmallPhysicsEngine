#include "Simulation.hpp"

Simulation::Simulation() :
  sdl_window{"Simulation"}, sdl_renderer{sdl_window.ptr.Get()} {}

void Simulation::Run() {
  while(input_handler.Continue()) {
    sdl_renderer.Render();
  }
}
