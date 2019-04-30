#ifndef SDLRENDERER_HPP
#define SDLRENDERER_HPP

#include <unordered_map>
#include <string>
#include "ParticleContainer.hpp"
#include "ImmovableContainer.hpp"
#include "SDLBase.hpp"
#include "SDLPointer.hpp"
#include "SDLTexture.hpp"

class SDLRenderer : public SDLBase {
  using TextureInterface = std::vector<SDL_Texture*>;
public:
  SDLRenderer(SDL_Window * const sdl_window, int const index = -1,
	      Uint32 const flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC,
	      SDL_Color const & in_background_color = {255, 255, 255, 255});
  SDLRenderer(SDLRenderer const & copy_from) = delete;
  SDLRenderer & operator=(SDLRenderer const & copy_from) = delete;
  SDLRenderer(SDLRenderer && move_from) = default;
  SDLRenderer & operator=(SDLRenderer && move_from) = default;
  virtual ~SDLRenderer();
  void AddParticleTexture(int const diameter, SDL_Color const & color);
  void AddImmovableTexture(int const diameter, SDL_Color const & color);
  void Render(ParticleContainer const & particles, ImmovableContainer const & immovables);
private:
  void AddTexture(TextureInterface & texture_interface, int const diameter, SDL_Color const & color);
  template<class Container> void Render(Container const & container,
					TextureInterface const & texture_interface);
  SDL_Rect GetRectFromCircle(double const pos_x, double const pos_y, double const radius);
  void PrimitiveRenderCircle(double const pos_x, double const pos_y, double const radius);
  void TextureRenderCircle(double const pos_x, double const pos_y,
			   double const radius, SDL_Texture * sdl_texture);
  SDLPointer<SDL_Renderer> ptr;
  std::unordered_map<std::string, SDLPointer<SDL_Texture>> texture_map;
  TextureInterface particle_texture_interface;
  TextureInterface immovable_texture_interface;
  SDL_Color background_color;
};

template<class Container> void SDLRenderer::Render(Container const & container,
						   TextureInterface const & texture_interface) {
  for(typename Container::size_type i{0}, size{container.size()}; i < size; ++i) {
    auto & object{container[i]};
    if(texture_interface[i])
      TextureRenderCircle(object.pos_x, object.pos_y, object.radius, texture_interface[i]);
    else PrimitiveRenderCircle(object.pos_x, object.pos_y, object.radius);
  }
}

#endif
