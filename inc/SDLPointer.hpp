#ifndef SDLPOINTER_HPP
#define SDLPOINTER_HPP

#include <iostream>
#include <SDL.h>
#include "Utility.hpp"

template<class PointerType, class Deleter = void(*)(PointerType*)>
struct SDLPointer {
  SDLPointer(PointerType * in_data, Deleter in_deleter);
  ~SDLPointer();
  PointerType * data;
  Deleter deleter;
};

template<class PointerType, class Deleter>
SDLPointer<PointerType, Deleter>::SDLPointer(PointerType * in_data, Deleter in_deleter) :
  data{in_data}, deleter{in_deleter} {
  if(!SDL_WasInit(SDL_INIT_VIDEO) && SDL_Init(SDL_INIT_VIDEO) != 0) {
    throw std::runtime_error("SDL could not initialize, SDL_Error: "+std::string{SDL_GetError()});
  }      
}

template<class PointerType, class Deleter>
SDLPointer<PointerType, Deleter>::~SDLPointer() {
  if(data) {
    if(SDL_WasInit(SDL_INIT_VIDEO)) {
      deleter(data);
    } else {
      Utility::Warning("Unable to destroy SDLPointer");
    }
  }
}

#endif
