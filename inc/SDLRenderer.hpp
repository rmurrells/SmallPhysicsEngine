#ifndef SDLRENDERER_HPP
#define SDLRENDERER_HPP

#include "ParticleContainer.hpp"
#include "SDLPointer.hpp"
#include "SDLTexture.hpp"

class SDLRenderer {
public:
  SDLRenderer(SDL_Window * const sdl_window, int const index = -1,
	      Uint32 const flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  template<class ColorType> void AddTexture(int const diameter, ColorType const & sdl_color);
  void Render(ParticleContainer const & particles);
private:
  SDL_Rect GetRectFromParticle(Particle const & particle);
  void PrimitiveRender(Particle const & particle);
  void TextureRender(Particle const & particle, SDL_Texture * sdl_texture);
  SDLPointer<SDL_Renderer> ptr;
  std::vector<SDLPointer<SDL_Texture>> textures;
};

template<class ColorType>
void SDLRenderer::AddTexture(int const diameter, ColorType const & color) {
  textures.push_back(SDLTexture::InitializeCircle(ptr.Get(), diameter, color));
}

#endif
