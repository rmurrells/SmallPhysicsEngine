#include "SDLRenderer.hpp"

SDLRenderer::SDLRenderer(SDL_Window * const sdl_window, int const index, Uint32 const flags) :
  ptr{SDL_CreateRenderer(sdl_window, index, flags), SDL_DestroyRenderer},
  sdl_texture{"../bmp/dot.bmp", ptr.Get()} {
  if(!ptr.Get()) {
    throw std::runtime_error("SDL_Renderer could not be created, SDL_Error: "+std::string{SDL_GetError()});
  }
}

void SDLRenderer::Render(ParticleContainer const & particles) {
  SDL_SetRenderDrawColor(ptr.Get(), 255, 255, 255, 1);
  SDL_RenderClear(ptr.Get());
  for(auto & particle : particles) {
    if(sdl_texture.Get()) {
      TextureRender(particle);
    } else {
      PrimitiveRender(particle);
    }
  }
  SDL_RenderPresent(ptr.Get());
}

SDL_Rect SDLRenderer::GetRectFromParticle(Particle const & particle) {
  SDL_Rect sdl_rect;
  sdl_rect.x = static_cast<int>(particle.pos_x-particle.radius);
  sdl_rect.y = static_cast<int>(particle.pos_y-particle.radius);
  sdl_rect.w = static_cast<int>(2*particle.radius);
  sdl_rect.h = static_cast<int>(2*particle.radius);
  return sdl_rect;
}

void SDLRenderer::PrimitiveRender(Particle const & particle) {
  SDL_Rect sdl_rect{GetRectFromParticle(particle)};
  SDL_SetRenderDrawColor(ptr.Get(), 0, 0, 0, 255);
  SDL_RenderFillRect(ptr.Get(), &sdl_rect);  
}

void SDLRenderer::TextureRender(Particle const & particle) {
  SDL_Rect sdl_rect{GetRectFromParticle(particle)};
  SDL_RenderCopy(ptr.Get(), sdl_texture.Get(),  nullptr, &sdl_rect);
}
