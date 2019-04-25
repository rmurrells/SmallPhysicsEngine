#include "Simulation.hpp"
#include "Border.hpp"

Simulation::Simulation() :
  sdl_window{"Simulation"}, sdl_renderer{sdl_window.GetWindowPtr()},
  fps_capper{60} {}

std::pair<int, int> Simulation::GetWindowSize() const {
  return sdl_window.GetWindowSize();
}

void Simulation::SetBackgroundColor(SDL_Color const & color) {
  sdl_renderer.SetBackgroundColor(color);
}

void Simulation::SetBackgroundColor(Uint8 const r, Uint8 const g, Uint8 const b, Uint8 const a) {
  SetBackgroundColor({r, g, b, a});
}

void Simulation::AddParticle(double const pos_x, double const pos_y,
			     double const vel_x, double const vel_y,
			     double const radius, double const mass,
			     SDL_Color const & color, int const texture_size) {
  if constexpr(std::numeric_limits<double>::is_iec559) {
    if(std::isnan(pos_x) || std::isnan(pos_x) || std::isnan(vel_x) ||
       std::isnan(radius) || std::isnan(mass)) {
      Utility::Warning("Invalid particle not added to simulation - pos_x: "+
		       std::to_string(pos_x)+" pos_y: "+std::to_string(pos_y)+" vel_x: "+
		       std::to_string(vel_x)+" vel_y: "+std::to_string(vel_y)+" radius: "+
		       std::to_string(radius)+" mass: "+std::to_string(mass));
      return;
    }
  }
  if(radius < std::numeric_limits<double>::epsilon()) {
    Utility::Warning("Particle with radius == 0 not added to simulation");
    return;
  }
  if(mass < std::numeric_limits<double>::epsilon()) {
    Utility::Warning("Particle with mass == 0  not added to simulation");
    return;
  }
  particles.emplace_back(pos_x, pos_y, vel_x, vel_y, radius, mass);
  sdl_renderer.AddTexture(texture_size ? texture_size : std::max(static_cast<int>(radius*2), 21), color);
}

void Simulation::Run() {
  Border border{{0, 0}, sdl_window.GetWindowSize()};
  while(input_handler.Continue()) {
    SimpleParticleModel::Run(particles, border);
    sdl_renderer.Render(particles);
    fps_capper.SleepToNextFrame();
  }
}
