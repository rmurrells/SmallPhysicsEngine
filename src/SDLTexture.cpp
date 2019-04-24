#include "SDLTexture.hpp"
#include <cstring>
#include "SDL_image.h"
#include "Utility.hpp"

SDLPointer<SDL_Texture> SDLTexture::InitializeFromBMP(SDL_Renderer * renderer, std::string const & file_path) {
  SDLPointer<SDL_Surface> surface{IMG_Load(file_path.c_str()), SDL_FreeSurface};
  if(!surface.Get()) {
    Utility::SDLWarning("Could not load bitmap: "+file_path);
    return {nullptr, nullptr};
  }
  SDLPointer<SDL_Surface> formatted_surface{SDL_ConvertSurfaceFormat(surface.Get(),
								     SDL_PIXELFORMAT_RGBA8888, 0), SDL_FreeSurface};
  if(!formatted_surface.Get()) {
    Utility::SDLWarning("Could not convert bitmap surface: "+file_path);
    return {nullptr, nullptr};
  }
  if(SDL_SetColorKey(formatted_surface.Get(), SDL_TRUE, SDL_MapRGB(formatted_surface->format, 0, 255, 255)) > 0) {
    Utility::SDLWarning("Could not set color key for bitmap");
  }
  SDL_Texture * texture{SDL_CreateTextureFromSurface(renderer, formatted_surface.Get())};
  if(!texture) {
    Utility::SDLWarning("Could not create texture from bitmap: "+file_path);
  }
  return {texture, SDL_DestroyTexture};
}

SDLTexture::DrawCircle::DrawCircle(SDL_Surface * in_surface) : surface{in_surface} {
  if(SDL_MUSTLOCK(surface) && SDL_LockSurface(surface) < 0) {
    Utility::SDLWarning("Could not lock surface texture for circle");
    surface = nullptr;
  }
}
  
void SDLTexture::DrawCircle::operator()(Uint32 const color) {
  if(!surface) return;
  if(surface->format->BitsPerPixel != 32) {
    Utility::Warning("SDL_Surface pixels must be 32 bit to draw circle");
    return;
  }
  if(surface->w != surface->h) {
    Utility::Warning("Surface must have equal width and height to draw cirle");
    return;
  }
  int const diameter{surface->w};
  bool const even{diameter%2 == 0};
  int const radius{diameter/2}; int const radiussq{radius*radius};
  auto pixels{static_cast<Uint32*>(surface->pixels)};
  Uint32 const transparent{color ? Uint32{0} : Uint32{1}};
  for(int i{0}; i < diameter*diameter; ++i) pixels[i] = transparent;
  for(int i{0}; i < diameter*diameter; ++i) {
    int const px{i-diameter*(i/diameter)-radius};
    int const py{i/diameter-radius};
    if([radius, radiussq](int const x, int const y)
       {return x*x+y*y < radiussq+radius;}(px+(even && px > 0), py+(even && py > 0)))
      pixels[i] = color;
  }
  if(SDL_SetColorKey(surface, SDL_TRUE, transparent) > 0) {
    Utility::SDLWarning("Could not set color key for circle");
  }
}

void SDLTexture::DrawCircle::operator()(SDL_Color const & sdl_color) {
  this->operator()(SDL_MapRGBA(surface->format, sdl_color.r, sdl_color.g, sdl_color.b, sdl_color.a));
}
  
SDLTexture::DrawCircle::~DrawCircle() {
  if(surface && SDL_MUSTLOCK(surface)) SDL_UnlockSurface(surface);
}
