#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <vector>
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
  template<class... Args> void AddParticle(Args&&... args);
  void Run();
private:
  SDLHandler sdl_handler;
  SDLWindow sdl_window;
  SDLRenderer sdl_renderer;
  InputHandler input_handler;
  FPSCapper<std::chrono::microseconds> fps_capper;
  SimpleParticleModel particle_model;
  ParticleContainer particle_container;
};

template<class... Args> void Simulation::AddParticle(Args&&... args) {
  particle_container.AddParticle(args...);
}


#endif
