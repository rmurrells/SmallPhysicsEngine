#include "SDLBase.hpp"
#include "Utility.hpp"

int SDLBase::instance_counter{0};

SDLBase::SDLBase() {
  ++instance_counter;
  if(!SDL_WasInit(SDL_INIT_VIDEO) && SDL_Init(SDL_INIT_VIDEO) != 0) {
    Utility::SDLThrow("SDL could not initialize");
  }
}

SDLBase::SDLBase([[maybe_unused]] SDLBase && move_from) noexcept : SDLBase() {}
  
SDLBase::~SDLBase() {
  --instance_counter;
  if(instance_counter == 0) SDL_Quit();
}
