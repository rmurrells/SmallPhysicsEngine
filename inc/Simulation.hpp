#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include "SDLHandler.hpp"
#include "SDLWindow.hpp"
#include "SDLRenderer.hpp"
#include "InputHandler.hpp"

class Simulation {
public:
  Simulation();
  void Run();
private:
  SDLHandler sdl_handler;
  SDLWindow sdl_window;
  SDLRenderer sdl_renderer;
  InputHandler input_handler;
};

#endif
