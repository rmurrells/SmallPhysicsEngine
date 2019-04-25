#ifndef SDLRENDERER_HPP
#define SDLRENDERER_HPP

#include <unordered_map>
#include <string>
#include "ParticleContainer.hpp"
#include "SDLPointer.hpp"
#include "SDLTexture.hpp"

class SDLRenderer {
public:
  SDLRenderer(SDL_Window * const sdl_window, int const index = -1,
	      Uint32 const flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC,
	      SDL_Color const & in_background_color = {255, 255, 255, 255});
  void SetBackgroundColor(SDL_Color const & color);
  void AddTexture(int const diameter, SDL_Color const & color);
  void Render(ParticleContainer const & particles);
private:
  SDL_Rect GetRectFromParticle(Particle const & particle);
  void PrimitiveRender(Particle const & particle);
  void TextureRender(Particle const & particle, SDL_Texture * sdl_texture);
  SDLPointer<SDL_Renderer> ptr;
  std::unordered_map<std::string, SDLPointer<SDL_Texture>> texture_map;
  std::vector<SDL_Texture*> texture_interface;
  SDL_Color background_color;
};

#endif
