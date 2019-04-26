#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP

#include <SDL.h>
#include "MouseState.hpp"

class InputHandler {
public:
  MouseState const & GetMouseState() const;
  bool Continue();
private:
  SDL_Event sdl_event;
  MouseState mouse_state;
};

#endif
