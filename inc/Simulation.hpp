#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <type_traits>
#include "SDLHandler.hpp"
#include "SDLWindow.hpp"
#include "SDLRenderer.hpp"
#include "InputHandler.hpp"
#include "FPSCapper.hpp"
#include "ParticleContainer.hpp"
#include "ImmovableContainer.hpp"
#include "ParticleMover.hpp"
#include "SimpleParticleCollider.hpp"
#include "ImmovableParticleCollider.hpp"
#include "Border.hpp"
#include "MouseInteraction.hpp"

class Simulation {
public:
  Simulation(double const particle_damping = 1, double const coefficient_of_restitution = 1,
	     double const border_damping = 1, double const in_mouse_acceleration = 0);
  void AddParticle(double const pos_x, double const pos_y,
		   double const vel_x, double const vel_y,
		   double const radius, double const mass,
		   SDL_Color const & color = {0, 0, 0, 255}, int const texture_size = 0);
  void AddImmovable(double const pos_x, double const pos_y,
		    double const radius, SDL_Color const & color = {0, 0, 0, 255},
		    int const texture_size = 0);
  std::pair<int, int> GetWindowSize() const;
  void SetBackgroundColor(SDL_Color const & color);
  void SetBackgroundColor(Uint8 const r, Uint8 const g, Uint8 const b, Uint8 const a = 255);
  void Run();
private:
  SDLHandler sdl_handler;
  SDLWindow sdl_window;
  SDLRenderer sdl_renderer;
  InputHandler input_handler;
  FPSCapper<std::chrono::microseconds> fps_capper;
  ParticleContainer particles;
  ImmovableContainer immovables;
  ParticleMover particle_mover;
  SimpleParticleCollider simple_particle_collider;
  ImmovableParticleCollider immovable_particle_collider;
  Border border;
  MouseInteraction mouse_interaction;
};

#endif
