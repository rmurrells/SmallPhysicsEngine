#include "Utility.hpp"
#include <iostream>
#include <cmath>

void Utility::Warning(std::string const & message) {
  std::cout << "WARNING: " << message << '\n';
}

double Utility::DotProduct(double const ax, double const ay, double const bx, double const by) {
  return ax*bx+ay*by;
}

double Utility::Magnitude(double const x, double const y) {
  return std::sqrt(x*x+y*y);
}
