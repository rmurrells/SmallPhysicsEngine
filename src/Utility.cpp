#include "Utility.hpp"
#include <iostream>
#include <stdexcept>

void Utility::Warning(std::string const & message) {
  std::cout << "WARNING: " << message << '\n';
}

void Utility::SDLWarning(std::string const & message) {
  std::cout << "WARNING: " << message << ", SDL_Error: " << SDL_GetError() << '\n';
}

void Utility::SDLThrow(std::string const & message) {
  throw std::runtime_error(message+", SDL_Error: "+std::string{SDL_GetError()});
}
