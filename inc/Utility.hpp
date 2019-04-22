#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <string>

namespace Utility {
  void Warning(std::string const & message);
  double DotProduct(double const ax, double const ay, double const bx, double const by);
  double Magnitude(double const x, double const y);
}

#endif
