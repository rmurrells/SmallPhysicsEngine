#include "Simulation.hpp"
#include "Utility.hpp"
#include "Math.hpp"

Simulation::Simulation(double const particle_damping, double const coefficient_of_restitution,
		       double const border_damping, double const mouse_acceleration) :
  sdl_window{"Simulation"}, sdl_renderer{sdl_window.GetWindowPtr()}, fps_capper{60},
  particle_mover{particle_damping}, simple_particle_collider{coefficient_of_restitution},
  border{{0, 0}, sdl_window.GetWindowSize(), border_damping}, mouse_interaction{mouse_acceleration} {}

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
  auto GetValueString =
    [&]() {
      return "pos_x: "+std::to_string(pos_x)+" pos_y: "+std::to_string(pos_y)+
	" vel_x: "+std::to_string(vel_x)+" vel_y: "+std::to_string(vel_y)+
	" radius: "+std::to_string(radius)+" mass: "+std::to_string(mass);
    };
  if constexpr(std::numeric_limits<double>::is_iec559) {
    if(std::isnan(pos_x) || std::isnan(pos_y) || std::isnan(vel_x) || std::isnan(vel_y) ||
       std::isnan(radius) || std::isnan(mass)) {
      Utility::Warning("Invalid particle not added to simulation - "+GetValueString());
      return;
    }
  }
  if(radius < std::numeric_limits<double>::epsilon()) {
    Utility::Warning("Particle with radius == 0 not added to simulation - "+GetValueString());
    return;
  }
  if(mass < std::numeric_limits<double>::epsilon()) {
    Utility::Warning("Particle with mass == 0  not added to simulation - "+GetValueString());
    return;
  }
  if(radius < Math::Magnitude(vel_x, vel_y)) Utility::Warning("Particle radius should be >= particle speed - "+GetValueString());
  particles.emplace_back(pos_x, pos_y, vel_x, vel_y, radius, mass);
  sdl_renderer.AddParticleTexture(texture_size ? texture_size : std::max(static_cast<int>(radius*2), 21), color);
}

void Simulation::AddImmovable(double const pos_x, double const pos_y,
			      double const radius, SDL_Color const & color,
			      int const texture_size) {
  immovables.emplace_back(pos_x, pos_y, radius);
  sdl_renderer.AddImmovableTexture(texture_size ? texture_size : std::max(static_cast<int>(radius*2), 21), color);
}

void Simulation::Run() {
  while(input_handler.Continue()) {
    mouse_interaction.Radial(particles, input_handler.GetMouseState());
    particle_mover.Move(particles);
    simple_particle_collider.Collide(particles);
    immovable_particle_collider.Collide(particles, immovables);
    border.Collide(particles);
    sdl_renderer.Render(particles, immovables);
    fps_capper.SleepToNextFrame();
  }
}
