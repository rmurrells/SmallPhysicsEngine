#include "SimulationBuilder.hpp"

Simulation SimulationBuilder::Build() const {
  SDLWindow sdl_window{"Simulation", SDL_WINDOW_SHOWN, width, height};
  SDLRenderer sdl_renderer{sdl_window.GetWindowPtr(), -1,
			   SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC,
			   background_color};
  ParticleMover particle_mover{particle_motion_damping};
  SimpleParticleCollider simple_particle_collider{coefficient_of_restitution};
  Border border{{0, 0}, {width, height}, border_damping};
  MouseInteraction mouse_interaction{mouse_acceleration};
  return {std::move(sdl_window), std::move(sdl_renderer), particle_mover, simple_particle_collider,
	  border, mouse_interaction};
}

SimulationBuilder & SimulationBuilder::SetWindowSize(int const in_width, int const in_height) {
  width = in_width;
  height = in_height;
  return *this;
}

SimulationBuilder & SimulationBuilder::SetBackgroundColor(SDL_Color const & in_background_color) {
  background_color = in_background_color;
  return *this;
}

SimulationBuilder & SimulationBuilder::SetParticleMotionDamping(double const in_particle_motion_damping) {
  particle_motion_damping = in_particle_motion_damping;
  return *this;
}

SimulationBuilder & SimulationBuilder::SetParticleCR(double const in_coefficient_of_restitution) {
  coefficient_of_restitution = in_coefficient_of_restitution;
  return *this;
}

SimulationBuilder & SimulationBuilder::SetBorderCR(double const in_border_damping) {
  border_damping = in_border_damping;
  return *this;
}

SimulationBuilder & SimulationBuilder::SetMouseAccel(double const in_mouse_acceleration) {
  mouse_acceleration = in_mouse_acceleration;
  return *this;
}
