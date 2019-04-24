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
#include "Border.hpp"

class Simulation {
public:
  Simulation();
  void AddParticle(double const pos_x, double const pos_y,
		   double const vel_x, double const vel_y,
		   double const radius, double const mass,
		   SDL_Color const & color);
  void AddParticle(double const pos_x, double const pos_y,
		   double const vel_x, double const vel_y,
		   double const radius, double const mass,
		   Uint32 const color = 0);
  template<class ColorType>
  typename std::enable_if<
    std::is_same<ColorType, Uint8>::value == true ||
    std::is_same<ColorType, SDL_Color>::value == true>::type
  AddParticle(double const pos_x, double const pos_y,
	      double const vel_x, double const vel_y,
	      double const radius, double const mass,
	      ColorType const & color);
  void Run();
private:
  SDLHandler sdl_handler;
  SDLWindow sdl_window;
  SDLRenderer sdl_renderer;
  InputHandler input_handler;
  FPSCapper<std::chrono::microseconds> fps_capper;
  ParticleContainer particles;
};

#endif
