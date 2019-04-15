#include <cmath>
#include <math.h>
#include <iostream>
#include "Gravity.hpp"
#include "Particle.hpp"
//#include "GeneralSetting.hpp"

using namespace std;

void Gravity(Particle& part1, Particle& part2){
  double frame_gap = 0.1;
  double Force = (6.674e-11*part1.mass*part2.mass)/((part1.pos_x-part2.pos_x)*(part1.pos_x-part2.pos_x)+(part1.pos_y-part2.pos_y)*(part1.pos_y-part2.pos_y));
  double Acce1 = (Force/part1.mass);
  double Acce2 = (Force/part2.mass);
  double velocity1_y = Acce1*sin(atan((part1.pos_y-part2.pos_y)/(part1.pos_x-part2.pos_x)))*frame_gap + part1.vel_y;
  double velocity1_x = Acce1*cos(atan((part1.pos_y-part2.pos_y)/(part1.pos_x-part2.pos_x)))*frame_gap + part1.vel_x;
  double velocity2_y = Acce2*sin(atan((part1.pos_y-part2.pos_y)/(part1.pos_x-part2.pos_x)))*frame_gap + part2.vel_y;
  double velocity2_x = Acce2*cos(atan((part1.pos_y-part2.pos_y)/(part1.pos_x-part2.pos_x)))*frame_gap + part2.vel_x;  

  part1.vel_x = velocity1_x;
  part1.vel_y = velocity1_y;
  part2.vel_x = velocity2_x;
  part2.vel_y = velocity2_y;
  
}
