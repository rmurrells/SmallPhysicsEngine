#include "Math.hpp"
#include <cmath>

double Math::DotProduct(double const ax, double const ay, double const bx, double const by) {
  return ax*bx+ay*by;
}

double Math::Magnitude(double const x, double const y) {
  return std::sqrt(x*x+y*y);
}

