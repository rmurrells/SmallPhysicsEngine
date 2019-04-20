#ifndef SDLTEXTURE_HPP
#define SDLTEXTURE_HPP

#include <string>
#include "SDLPointer.hpp"

class SDLTexture {
public:
  SDLTexture(std::string const & file_path, SDL_Renderer * renderer);
  SDL_Texture * Get() const;
private:
  void FormatTexture(SDL_Surface * formatted_surface);
  SDL_Texture * Initialize(std::string const & file_path, SDL_Renderer * renderer);
  SDLPointer<SDL_Texture> ptr;
};

#endif
