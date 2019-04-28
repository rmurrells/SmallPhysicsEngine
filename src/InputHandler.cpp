#include "InputHandler.hpp"

MouseState const & InputHandler::GetMouseState() const {
  return mouse_state;
}

bool InputHandler::Continue() {
  while(SDL_PollEvent(&sdl_event) != 0) {
    switch(sdl_event.type) {
    case SDL_MOUSEBUTTONUP: {
      if(sdl_event.button.button == SDL_BUTTON_LEFT) mouse_state.left = false;
      else if(sdl_event.button.button == SDL_BUTTON_RIGHT) mouse_state.right = false;
      break;
    }
    case SDL_MOUSEBUTTONDOWN: {
      if(sdl_event.button.button == SDL_BUTTON_LEFT) mouse_state.left = true;
      else if(sdl_event.button.button == SDL_BUTTON_RIGHT) mouse_state.right = true;
      break;
    }
    case SDL_MOUSEMOTION: {
      mouse_state.x = sdl_event.motion.x;
      mouse_state.y = sdl_event.motion.y;
      break;
    }
    case SDL_QUIT: return false;
    case SDL_KEYDOWN: {
      if(sdl_event.key.keysym.sym == SDLK_ESCAPE) return false;
    }
  }
  }
  return true;
}
