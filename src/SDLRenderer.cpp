#include "SDLRenderer.hpp"

SDLRenderer::SDLRenderer(SDL_Window * const sdl_window, int const index, Uint32 const flags) :
  ptr{SDL_CreateRenderer(sdl_window, index, flags), SDL_DestroyRenderer} {
  if(!ptr.data) {
    throw std::runtime_error("SDL_Renderer could not be created, SDL_Error: "+std::string{SDL_GetError()});
  }
}

void SDLRenderer::Render() {
  SDL_SetRenderDrawColor(ptr.data, 255, 255, 255, 1);
  SDL_RenderClear(ptr.data);
  SDL_RenderPresent(ptr.data);
}
