#ifndef SDLTEXTURE_HPP
#define SDLTEXTURE_HPP

#include "SDLPointer.hpp"

namespace SDLTexture {
  SDLPointer<SDL_Texture> GetCircleTexture(SDL_Renderer * renderer, int const diameter, SDL_Color const & sdl_color);
}

#endif
