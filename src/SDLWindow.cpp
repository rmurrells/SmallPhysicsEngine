#include "SDLWindow.hpp"

SDLWindow::SDLWindow(std::string const & name, Uint32 const window_flags,
		     int const width, int const height,
		     int const position_x, int const position_y) :
  ptr{SDL_CreateWindow(name.c_str(), position_x, position_y, width, height, window_flags), SDL_DestroyWindow},
  refresh_rate{60} {
  if(!ptr.Get()) {
    throw std::runtime_error(std::string{"SDL_Window could not be created, SDL_Error: "}+SDL_GetError());
  }
  if(SDL_GetDesktopDisplayMode(SDL_GetWindowDisplayIndex(ptr.Get()), &sdl_display_mode) == 0) {
    refresh_rate = sdl_display_mode.refresh_rate;
  }
}

SDLWindow::~SDLWindow() = default;

SDL_Window * SDLWindow::GetWindowPtr() const {
  return ptr.Get();
}

int SDLWindow::GetRefreshRate() const {
  return refresh_rate;
}

std::pair<int, int> SDLWindow::GetWindowPosition() const {
  std::pair<int, int> ret;
  SDL_GetWindowPosition(ptr.Get(), &ret.first, &ret.second);
  return ret;
}

std::pair<int, int> SDLWindow::GetWindowSize() const {
  std::pair<int, int> ret;
  SDL_GetWindowSize(ptr.Get(), &ret.first, &ret.second);
  return ret;
}
