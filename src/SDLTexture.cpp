#include "SDLTexture.hpp"
#include <cstring>
#include "Utility.hpp"

SDLPointer<SDL_Texture> SDLTexture::GetCircleTexture(SDL_Renderer * renderer, int const diameter, SDL_Color const & sdl_color) {
  SDLPointer<SDL_Surface> surface{SDL_CreateRGBSurface(0, diameter, diameter,
						       sizeof(Uint32)*8, 0, 0, 0, 0), SDL_FreeSurface};
  if(!surface.Get()) {
    Utility::SDLWarning("Could not create surface for circle");
    return {nullptr, nullptr};
  }
  if(SDL_MUSTLOCK(surface.Get()) && SDL_LockSurface(surface.Get()) < 0) {
    Utility::SDLWarning("Could not lock surface texture for circle");
    return {nullptr, nullptr};
  }
  bool const even{diameter%2 == 0};
  int const radius{diameter/2}; int const radiussq{radius*radius};
  auto pixels{static_cast<Uint32*>(surface->pixels)};
  auto const color{SDL_MapRGBA(surface->format, sdl_color.r, sdl_color.g, sdl_color.b, sdl_color.a)};
  Uint32 const transparent{color ? Uint32{0} : Uint32{1}};
  for(int i{0}; i < diameter*diameter; ++i) {
    int const px{i-diameter*(i/diameter)-radius};
    int const py{i/diameter-radius};
    if([radius, radiussq](int const x, int const y)
       {return x*x+y*y < radiussq+radius;}(px+(even && px > 0), py+(even && py > 0))) {
      pixels[i] = color;
    } else {
      pixels[i] = transparent;
    }
  }
  if(SDL_SetColorKey(surface.Get(), SDL_TRUE, transparent) > 0) {
    Utility::SDLWarning("Could not set color key for circle");
  }
  if(SDL_MUSTLOCK(surface.Get())) SDL_UnlockSurface(surface.Get());
  SDL_Texture * texture{SDL_CreateTextureFromSurface(renderer, surface.Get())};
  if(!texture) {
    Utility::SDLWarning("Could not create texture for circle");
    return {nullptr, nullptr};
  }
  return {texture, SDL_DestroyTexture};
}
