#ifndef SDLTEXTURE_HPP
#define SDLTEXTURE_HPP

#include <string>
#include "SDLPointer.hpp"

namespace SDLTexture {
  //SDLPointer<SDL_Texture> InitializeFromBMP(SDL_Renderer * renderer, std::string const & file_path);
  SDLPointer<SDL_Texture> GetCircleTexture(SDL_Renderer * renderer, int const diameter, SDL_Color const & sdl_color);
}

#endif
