#ifndef PARTICLE_HPP
#define PARTICLE_HPP

struct Particle {
  Particle(int in_pos_x, int in_pos_y, double in_radius, double in_mass) :
    pos_x{in_pos_x}, pos_y{in_pos_y}, vel_x{0}, vel_y{0}, radius{in_radius}, mass{in_mass} {}
  int pos_x;
  int pos_y;
  int vel_x;
  int vel_y;
  double radius;
  double mass;
};

#endif
