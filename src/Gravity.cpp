#include <cmath>
#include "Gravity.hpp"

using namespace std;

void LoopGravity(ParticleContainer& particles, double framerate){
  for(ParticleContainer::size_type i=0; i<(particles.size()-1); ++i){
    for(ParticleContainer::size_type j=(i+1); j<particles.size(); ++j){
      Gravity(particles.at(i),particles.at(j),framerate);
    }
  }
}

void Gravity(Particle& part1, Particle& part2, double framerate){
  double y_vec = (part1.pos_y-part2.pos_y);
  double x_vec = (part1.pos_x-part2.pos_x);
  double mag_sq = pow(y_vec,2)+pow(x_vec,2);
  double mag = sqrt(mag_sq);
  double Force = (6.674e0*part1.mass*part2.mass)/mag_sq;
  double Acce1 = -(Force/part1.mass);
  double Acce2 = (Force/part2.mass);
  double ydir = y_vec/mag;
  double xdir = x_vec/mag;
  double velocity1_y = Acce1*ydir*framerate;
  double velocity1_x = Acce1*xdir*framerate; 
  double velocity2_y = Acce2*ydir*framerate; 
  double velocity2_x = Acce2*xdir*framerate; 
  
  part1.vel_x += velocity1_x;
  part1.vel_y += velocity1_y;
  part2.vel_x += velocity2_x;
  part2.vel_y += velocity2_y;
  
}
