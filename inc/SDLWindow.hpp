#ifndef SDLWINDOW_HPP
#define SDLWINDOW_HPP

#include <string>
#include <SDL.h>
#include "SDLBase.hpp"
#include "SDLPointer.hpp"

class SDLWindow : public SDLBase {
public:
  SDLWindow(std::string const & name, Uint32 const window_flags = SDL_WINDOW_SHOWN,
	    int const width = 800, int const height = 600,
            int const position_x = SDL_WINDOWPOS_UNDEFINED, int const position_y = SDL_WINDOWPOS_UNDEFINED);
  SDLWindow(SDLWindow const & copy_from) = delete;
  SDLWindow & operator=(SDLWindow const & copy_from) = delete;
  SDLWindow(SDLWindow && move_from) = default;
  SDLWindow & operator=(SDLWindow && move_from) = default;
  virtual ~SDLWindow();
  SDL_Window * GetWindowPtr() const;
  int GetRefreshRate() const;
  std::pair<int, int> GetWindowPosition() const;
  std::pair<int, int> GetWindowSize() const;
private:
  SDLPointer<SDL_Window> ptr;
  SDL_DisplayMode sdl_display_mode;
  int refresh_rate;
};

#endif
