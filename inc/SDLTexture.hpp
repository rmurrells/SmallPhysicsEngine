#ifndef SDLTEXTURE_HPP
#define SDLTEXTURE_HPP

#include <string>
#include "SDLPointer.hpp"

namespace SDLTexture {

  SDLPointer<SDL_Texture> InitializeFromBMP(SDL_Renderer * renderer, std::string const & file_path);
  
  class DrawCircle {
  public:
    DrawCircle(SDL_Surface * in_surface);
    void operator()(Uint32 const color);
    void operator()(SDL_Color const & sdl_color);
    ~DrawCircle();
  private:
    SDL_Surface * surface;
  };

  template<class ColorType>
  SDLPointer<SDL_Texture> InitializeCircle(SDL_Renderer * renderer, int const diameter, ColorType const & color) {
    SDLPointer<SDL_Surface> surface{SDL_CreateRGBSurface(0, diameter, diameter,
							 sizeof(Uint32)*8, 0, 0, 0, 0), SDL_FreeSurface};
    if(!surface.Get()) {
      Utility::SDLWarning("Could not create surface for circle");
      return {nullptr, nullptr};
    }
    DrawCircle(surface.Get())(color);
    SDL_Texture * texture{SDL_CreateTextureFromSurface(renderer, surface.Get())};
    if(!texture) Utility::SDLWarning("Could not create texture for circle");    
    return {texture, SDL_DestroyTexture};
  }
  
}

#endif
