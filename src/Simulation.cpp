#include "Simulation.hpp"

Simulation::Simulation() :
  sdl_window{"Simulation"}, sdl_renderer{sdl_window.ptr.data} {}

void Simulation::Run() {
  while(input_handler.Continue()) {
    
  }
}