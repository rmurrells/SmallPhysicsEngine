#include "SDLWindow.hpp"

SDLWindow::SDLWindow(std::string const & name, Uint32 const window_flags,
		     int const width, int const height,
		     int const position_x,
		     int const position_y) :
  ptr{SDL_CreateWindow(name.c_str(), position_x, position_y, width, height, window_flags), SDL_DestroyWindow},
  refresh_rate{60} {
  if(!ptr.data) {
    throw std::runtime_error(std::string{"SDL_Window could not be created, SDL_Error: "}+SDL_GetError());
  }
  if(SDL_GetDesktopDisplayMode(SDL_GetWindowDisplayIndex(ptr.data), &sdl_display_mode) == 0) {
    refresh_rate = sdl_display_mode.refresh_rate;
  }
}
