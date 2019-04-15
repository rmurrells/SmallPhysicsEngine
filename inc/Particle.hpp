#ifndef PARTICLE_HPP
#define PARTICLE_HPP

struct Particle {
  Particle(double in_pos_x, double in_pos_y, double in_radius, double in_mass) :
    pos_x{in_pos_x}, pos_y{in_pos_y}, vel_x{0}, vel_y{0}, radius{in_radius}, mass{in_mass} {}
  double pos_x;
  double pos_y;
  double vel_x;
  double vel_y;
  double radius;
  double mass;
};

#endif
