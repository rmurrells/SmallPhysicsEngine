#include "Border.hpp"

Border::Border(double const in_xmin, double const in_xmax,
	       double const in_ymin, double const in_ymax) :
  xmin{in_xmin}, xmax{in_xmax}, ymin{in_ymin}, ymax{in_ymax} {}

Border::Border(std::pair<double, double> const & boundary_position,
	       std::pair<double, double> const & boundary_size) :
  Border(boundary_position.first, boundary_size.first,
	 boundary_position.second, boundary_size.second) {}
