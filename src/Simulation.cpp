#include "Simulation.hpp"

Simulation::Simulation() :
  sdl_window{"Simulation"}, sdl_renderer{sdl_window.GetWindowPtr()},
  fps_capper{60} {}

void Simulation::AddParticle(double const pos_x, double const pos_y,
			     double const vel_x, double const vel_y,
			     double const radius, double const mass,
			     SDL_Color const & color) {
  particles.emplace_back(pos_x, pos_y, vel_x, vel_y, radius, mass);
  sdl_renderer.AddTexture(23, color);
}

void Simulation::AddParticle(double const pos_x, double const pos_y,
			     double const vel_x, double const vel_y,
			     double const radius, double const mass,
			     Uint32 const color) {
  particles.emplace_back(pos_x, pos_y, vel_x, vel_y, radius, mass);
  sdl_renderer.AddTexture(23, color);
}

void Simulation::Run() {
  Border border{{0, 0}, sdl_window.GetWindowSize()};
  while(input_handler.Continue()) {
    SimpleParticleModel::Run(particles, border);
    sdl_renderer.Render(particles);
    fps_capper.SleepToNextFrame();
  }
}
