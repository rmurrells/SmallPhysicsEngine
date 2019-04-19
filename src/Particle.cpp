#include "Particle.hpp"

Particle::Particle(double const in_pos_x, double const in_pos_y,
		   double const in_vel_x, double const in_vel_y,
		   double const in_radius, double const in_mass) :
  pos_x{in_pos_x}, pos_y{in_pos_y},
  vel_x{in_vel_x}, vel_y{in_vel_y},
  radius{in_radius}, mass{in_mass} {}
