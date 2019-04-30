#ifndef BORDER_HPP
#define BORDER_HPP

#include <utility>
#include "ParticleContainer.hpp"

struct Border {
  Border(double const in_xmin, double const in_xmax,
	 double const in_ymin, double const in_ymax,
	 double const in_coefficient_of_restitution = 1);
  Border(std::pair<double, double> const & boundary_position,
	 std::pair<double, double> const & boundary_size,
	 double const in_coefficient_of_restitution = 1);
  void Collide(ParticleContainer & particle_container);
  double xmin;
  double xmax;
  double ymin;
  double ymax;
  double coefficient_of_restitution;
};

#endif
