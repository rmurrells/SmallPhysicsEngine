#ifndef SDLRENDERER_HPP
#define SDLRENDERER_HPP

#include "SDLPointer.hpp"
#include "ParticleContainer.hpp"

class SDLRenderer {
public:
  SDLRenderer(SDL_Window * const sdl_window, int const index = -1, Uint32 const flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  void Render(ParticleContainer const & particles);
private:
  void PrimitiveRender(Particle const & particle);
  SDLPointer<SDL_Renderer> ptr;
};

#endif
