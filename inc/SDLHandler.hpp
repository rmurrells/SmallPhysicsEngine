#ifndef SDLHANDLER_HPP
#define SDLHANDLER_HPP

#include <stdexcept>
#include <string>
#include <SDL.h>

struct SDLHandler {
  SDLHandler() {
    if(!SDL_WasInit(SDL_INIT_VIDEO) && SDL_Init(SDL_INIT_VIDEO) != 0) {
      throw std::runtime_error("SDL could not initialize, SDL_Error: "+std::string{SDL_GetError()});
    }
  }
  ~SDLHandler() {
    SDL_Quit();
  }
};

#endif
