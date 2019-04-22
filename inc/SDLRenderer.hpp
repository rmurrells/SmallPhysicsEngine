#ifndef SDLRENDERER_HPP
#define SDLRENDERER_HPP

#include "ParticleContainer.hpp"
#include "SDLPointer.hpp"
#include "SDLTexture.hpp"

class SDLRenderer {
public:
  SDLRenderer(SDL_Window * const sdl_window, int const index = -1, Uint32 const flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  void Render(ParticleContainer const & particles);
private:
  SDL_Rect GetRectFromParticle(Particle const & particle);
  void PrimitiveRender(Particle const & particle);
  void TextureRender(Particle const & particle);
  SDLPointer<SDL_Renderer> ptr;
  SDLTexture sdl_texture;
};

#endif
