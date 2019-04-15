#ifndef SDLWINDOW_HPP
#define SDLWINDOW_HPP

#include <string>
#include <SDL.h>
#include "SDLPointer.hpp"

class SDLWindow {
public:
  SDLWindow(std::string const & name, Uint32 const window_flags = SDL_WINDOW_SHOWN,
	    int const width = 800, int const height = 600,
            int const position_x = SDL_WINDOWPOS_UNDEFINED,
	    int const position_y = SDL_WINDOWPOS_UNDEFINED);
  SDLPointer<SDL_Window> ptr;
private:
  SDL_DisplayMode sdl_display_mode;
  int refresh_rate;
};

#endif