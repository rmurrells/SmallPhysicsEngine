#ifndef PARTICLE_HPP
#define PARTICLE_HPP

class Particle {
public:
  Particle(double const in_pos_x, double const in_pos_y,
	   double const in_vel_x, double const in_vel_y,
	   double const in_mass, double const in_radius);
  double pos_x;
  double pos_y;
  double vel_x;
  double vel_y;
  double mass;
  double radius;
};

#endif
