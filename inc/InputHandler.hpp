#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP

#include <SDL.h>

class InputHandler {
public:
  bool Continue();
private:
  SDL_Event sdl_event;
};

#endif
