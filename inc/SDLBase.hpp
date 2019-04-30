#ifndef SDLBASE_HPP
#define SDLBASE_HPP

#include <SDL.h>

class SDLBase {
public:
  SDLBase();
  SDLBase(SDLBase const & copy_from) = delete;
  SDLBase & operator=(SDLBase const & copy_from) = delete;
  SDLBase(SDLBase && move_from) noexcept;
  SDLBase & operator=(SDLBase && copy_from) = delete;
  virtual ~SDLBase();
private:
  static int instance_counter;
};

#endif
