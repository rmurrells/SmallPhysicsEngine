#ifndef SIMULATION_HPP
#define SIMULATION_HPP

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
  ParticleContainer particles;
};

template<class... Args> void Simulation::AddParticle(Args&&... args) {
  particles.emplace_back(args...);
}


#endif
