#include "Simulation.hpp"

Simulation::Simulation() :
  sdl_window{"Simulation"}, sdl_renderer{sdl_window.GetWindowPtr()} {}

void Simulation::Load() {
  auto const [iwidth, iheight] = sdl_window.GetWindowSize();
  double const width{static_cast<double>(iwidth)};
  double const height{static_cast<double>(iheight)};
  double const vel_x{1}; double const vel_y{1};
  double const radius{4};
  double const mass{1};
  particles.AddParticle(width/4, height/4, vel_x, vel_y, radius, mass);
  particles.AddParticle(3*width/4, height/4, vel_x, vel_y, radius, mass);
  particles.AddParticle(width/4, 3*height/4, vel_x, vel_y, radius, mass);
  particles.AddParticle(3*width/4, 3*height/4, vel_x, vel_y, radius, mass);
}

void Simulation::Run() {
  Load();
  while(input_handler.Continue()) {
    sdl_renderer.Render(particles);
  }
}
