#include "Utility.hpp"
#include <iostream>

void Utility::Warning(std::string const & message) {
  std::cout << "WARNING: " << message << '\n';
}

void Utility::SDLWarning(std::string const & message) {
  std::cout << "WARNING: " << message << ", SDL_Error: " << SDL_GetError() << '\n';
}
