#ifndef SDLPOINTER_HPP
#define SDLPOINTER_HPP

#include <iostream>
#include <SDL.h>
#include "Utility.hpp"

template<class PointerType, class Deleter = void(*)(PointerType*)>
struct SDLPointer {
  SDLPointer(PointerType * in_data, Deleter in_deleter);
  SDLPointer(SDLPointer const & copy_from) = delete;
  SDLPointer & operator=(SDLPointer const & move_from) = delete;
  SDLPointer(SDLPointer && move_from);
  SDLPointer & operator=(SDLPointer && move_from) = delete;
  ~SDLPointer();
  PointerType * Get() const;
private:
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
SDLPointer<PointerType, Deleter>::SDLPointer(SDLPointer && move_from) {
  data = move_from.data; move_from.data = nullptr;
  deleter = move_from.deleter;
}

template<class PointerType, class Deleter>
SDLPointer<PointerType, Deleter>::~SDLPointer() {
  if(data) {
    if(SDL_WasInit(SDL_INIT_VIDEO)) deleter(data);
    else Utility::Warning("Unable to destroy SDLPointer");
  }
}

template<class PointerType, class Deleter>
PointerType * SDLPointer<PointerType, Deleter>::Get() const {
  return data;
}

#endif
