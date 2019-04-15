#include "Utility.hpp"
#include <iostream>

void Utility::Warning(std::string const & message) {
  std::cout << "WARNING: " << message << '\n';
}
