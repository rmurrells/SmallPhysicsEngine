#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <type_traits>
#include "SDLHandler.hpp"
#include "SDLWindow.hpp"
#include "SDLRenderer.hpp"
#include "InputHandler.hpp"
#include "SimpleParticleModel.hpp"
#include "FPSCapper.hpp"
#include "ParticleContainer.hpp"

class Simulation {
public:
  Simulation();
  void AddParticle(double const pos_x, double const pos_y,
		   double const vel_x, double const vel_y,
		   double const radius, double const mass,
		   Uint32 const color = 0, int const texture_size = 0);
  void AddParticle(double const pos_x, double const pos_y,
		   double const vel_x, double const vel_y,
		   double const radius, double const mass,
		   SDL_Color const & color, int const texture_size = 0);
  void Run();
private:
  template<class ColorType>
  typename std::enable_if<
    std::is_same<ColorType, Uint32>::value == true ||
    std::is_same<ColorType, SDL_Color>::value == true>::type
  AddParticleImpl(double const pos_x, double const pos_y,
		  double const vel_x, double const vel_y,
		  double const radius, double const mass,
		  ColorType const & color, int const texture_size = 0);
  SDLHandler sdl_handler;
  SDLWindow sdl_window;
  SDLRenderer sdl_renderer;
  InputHandler input_handler;
  FPSCapper<std::chrono::microseconds> fps_capper;
  ParticleContainer particles;
};

template<class ColorType>
typename std::enable_if<
  std::is_same<ColorType, Uint32>::value == true ||
  std::is_same<ColorType, SDL_Color>::value == true>::type
Simulation::AddParticleImpl(double const pos_x, double const pos_y,
			    double const vel_x, double const vel_y,
			    double const radius, double const mass,
			    ColorType const & color, int const texture_size) {
  particles.emplace_back(pos_x, pos_y, vel_x, vel_y, radius, mass);
  sdl_renderer.AddTexture(texture_size ? texture_size : static_cast<int>(radius*2), color);
}

#endif
