#ifndef BORDER_HPP
#define BORDER_HPP

#include <utility>

struct Border {
  Border(double const in_xmin, double const in_xmax,
	 double const in_ymin, double const in_ymax);
  Border(std::pair<double, double> const & boundary_position,
	 std::pair<double, double> const & boundary_size);
  double xmin;
  double xmax;
  double ymin;
  double ymax;
};

#endif
