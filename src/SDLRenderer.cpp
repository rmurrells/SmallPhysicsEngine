#include "SDLRenderer.hpp"

SDLRenderer::SDLRenderer(SDL_Window * const sdl_window, int const index,
			 Uint32 const flags,
			 SDL_Color const & in_background_color) :
  ptr{SDL_CreateRenderer(sdl_window, index, flags), SDL_DestroyRenderer},
  background_color{in_background_color} {
  if(!ptr.Get()) throw std::runtime_error("SDL_Renderer could not be created, SDL_Error: "+std::string{SDL_GetError()});
}

SDLRenderer::~SDLRenderer() = default;

void SDLRenderer::SetBackgroundColor(SDL_Color const & color) {
  background_color = color;
}

void SDLRenderer::AddParticleTexture(int const diameter, SDL_Color const & color) {
  AddTexture(particle_texture_interface, diameter, color);
}

void SDLRenderer::AddImmovableTexture(int const diameter, SDL_Color const & color) {
  AddTexture(immovable_texture_interface, diameter, color);
}

void SDLRenderer::Render(ParticleContainer const & particles, ImmovableContainer const & immovables) {
  SDL_SetRenderDrawColor(ptr.Get(), background_color.r, background_color.g,
			 background_color.b, background_color.a);
  SDL_RenderClear(ptr.Get());
  Render(immovables, immovable_texture_interface);
  Render(particles, particle_texture_interface);
  SDL_RenderPresent(ptr.Get());
}

void SDLRenderer::AddTexture(TextureInterface & texture_interface, int const diameter, SDL_Color const & color) {
  texture_interface.emplace_back
    (texture_map.emplace(std::to_string(diameter)+std::to_string(color.r)+
			 std::to_string(color.g)+std::to_string(color.b)+
			 std::to_string(color.a),
			 SDLTexture::GetCircleTexture(ptr.Get(), diameter, color)).first->second.Get());
}

SDL_Rect SDLRenderer::GetRectFromCircle(double const pos_x, double const pos_y, double const radius) {
  return {static_cast<int>(pos_x-radius), static_cast<int>(pos_y-radius),
	  static_cast<int>(2*radius), static_cast<int>(2*radius)};
}

void SDLRenderer::PrimitiveRenderCircle(double const pos_x, double const pos_y, double const radius) {
  SDL_Rect sdl_rect{GetRectFromCircle(pos_x, pos_y, radius)};
  SDL_SetRenderDrawColor(ptr.Get(), 0, 0, 0, 255);
  SDL_RenderFillRect(ptr.Get(), &sdl_rect);  
}

void SDLRenderer::TextureRenderCircle(double const pos_x, double const pos_y,
				      double const radius, SDL_Texture * sdl_texture) {
  SDL_Rect sdl_rect{GetRectFromCircle(pos_x, pos_y, radius)};
  SDL_RenderCopy(ptr.Get(), sdl_texture, nullptr, &sdl_rect);
}
