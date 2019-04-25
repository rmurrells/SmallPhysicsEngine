#include "Simulation.hpp"
#include "Border.hpp"

Simulation::Simulation() :
  sdl_window{"Simulation"}, sdl_renderer{sdl_window.GetWindowPtr()},
  fps_capper{60} {}

void Simulation::AddParticle(double const pos_x, double const pos_y,
			     double const vel_x, double const vel_y,
			     double const radius, double const mass,
			     Uint32 const color, int const texture_radius) {
  AddParticleImpl<Uint32>(pos_x, pos_y, vel_x, vel_y, radius, mass, color, texture_radius);
}

void Simulation::AddParticle(double const pos_x, double const pos_y,
			     double const vel_x, double const vel_y,
			     double const radius, double const mass,
			     SDL_Color const & color, int const texture_radius) {
  AddParticleImpl<SDL_Color>(pos_x, pos_y, vel_x, vel_y, radius, mass, color, texture_radius);
}

void Simulation::Run() {
  Border border{{0, 0}, sdl_window.GetWindowSize()};
  while(input_handler.Continue()) {
    SimpleParticleModel::Run(particles, border);
    sdl_renderer.Render(particles);
    fps_capper.SleepToNextFrame();
  }
}
