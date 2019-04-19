#include "SDLRenderer.hpp"

SDLRenderer::SDLRenderer(SDL_Window * const sdl_window, int const index, Uint32 const flags) :
  ptr{SDL_CreateRenderer(sdl_window, index, flags), SDL_DestroyRenderer} {
  if(!ptr.Get()) {
    throw std::runtime_error("SDL_Renderer could not be created, SDL_Error: "+std::string{SDL_GetError()});
  }
}

void SDLRenderer::Render(ParticleContainer const & particles) {
  SDL_SetRenderDrawColor(ptr.Get(), 255, 255, 255, 1);
  SDL_RenderClear(ptr.Get());
  for(auto & particle : particles.GetParticles()) {
    
  }
  SDL_RenderPresent(ptr.Get());
}
