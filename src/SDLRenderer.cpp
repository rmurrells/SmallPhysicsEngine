#include "SDLRenderer.hpp"

SDLRenderer::SDLRenderer(SDL_Window * const sdl_window, int const index,
			 Uint32 const flags,
			 SDL_Color const & in_background_color) :
  ptr{SDL_CreateRenderer(sdl_window, index, flags), SDL_DestroyRenderer},
  background_color{in_background_color} {
  if(!ptr.Get()) throw std::runtime_error("SDL_Renderer could not be created, SDL_Error: "+std::string{SDL_GetError()});
}

void SDLRenderer::SetBackgroundColor(SDL_Color const & color) {
  background_color = color;
}

void SDLRenderer::AddTexture(int const diameter, SDL_Color const & color) {
  texture_interface.emplace_back
    (texture_map.emplace(std::to_string(diameter)+std::to_string(color.r)+
			 std::to_string(color.g)+std::to_string(color.b)+
			 std::to_string(color.a),
			 SDLTexture::GetCircleTexture(ptr.Get(), diameter, color)).first->second.Get());
}

void SDLRenderer::Render(ParticleContainer const & particles) {
  SDL_SetRenderDrawColor(ptr.Get(), background_color.r, background_color.g,
			 background_color.b, background_color.a);
  SDL_RenderClear(ptr.Get());
  for(ParticleContainer::size_type i = 0; i < particles.size(); ++i) {
    auto & particle = particles[i];
    if(texture_interface[i]) TextureRender(particle, texture_interface[i]);
    else PrimitiveRender(particle);
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

void SDLRenderer::TextureRender(Particle const & particle, SDL_Texture * sdl_texture) {
  SDL_Rect sdl_rect{GetRectFromParticle(particle)};
  SDL_RenderCopy(ptr.Get(), sdl_texture, nullptr, &sdl_rect);
}
