#include "SDLTexture.hpp"
#include "SDL_image.h"
#include "Utility.hpp"

SDLTexture::SDLTexture(std::string const & file_path, SDL_Renderer * renderer) :
  ptr{Initialize(file_path, renderer), SDL_DestroyTexture} {};

void SDLTexture::FormatTexture(SDL_Surface * formatted_surface) {
  if(SDL_SetColorKey(formatted_surface, SDL_TRUE, SDL_MapRGB(formatted_surface->format, 0, 255, 255)) > 0) {
    Utility::Warning("Could not set color key, SDL_Error: "+std::string{SDL_GetError()});
  }
}

SDL_Texture * SDLTexture::Initialize(std::string const & file_path, SDL_Renderer * renderer) {
  SDL_Surface * loaded_surface{IMG_Load(file_path.c_str())};
  if(!loaded_surface) {
    Utility::Warning("Could not load: "+file_path+", SDL_Error: "+std::string{SDL_GetError()});
    return nullptr;
  }
  SDL_Surface * formatted_surface{SDL_ConvertSurfaceFormat(loaded_surface, SDL_PIXELFORMAT_RGBA8888, 0)};
  if(!formatted_surface) {
    Utility::Warning("Could not convert: "+file_path+" to display format, SDL_Error: "+std::string{SDL_GetError()});
    return nullptr;
  }
  FormatTexture(formatted_surface);
  SDL_Texture * texture{SDL_CreateTextureFromSurface(renderer, formatted_surface)};
  if(!formatted_surface) {
    Utility::Warning("Could not create texture from: "+file_path+", SDL_Error: "+std::string{SDL_GetError()});
  }
  SDL_FreeSurface(formatted_surface);
  SDL_FreeSurface(loaded_surface);
  return texture;
}

SDL_Texture * SDLTexture::Get() const {
  return ptr.Get();
}
