#include "InputHandler.hpp"

bool InputHandler::Continue() {
  while(SDL_PollEvent(&sdl_event) != 0) {
    if(sdl_event.type == SDL_QUIT) return false;
  }
  return true;
}
