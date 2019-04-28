#include "Border.hpp"
#include "Utility.hpp"

Border::Border(double const in_xmin, double const in_xmax,
	       double const in_ymin, double const in_ymax,
	       double const in_damping_factor) :
  xmin{in_xmin}, xmax{in_xmax}, ymin{in_ymin}, ymax{in_ymax}, damping_factor{in_damping_factor} {
  if(damping_factor > 1) {
    Utility::Warning("Chosen Border damping factor: "+std::to_string(damping_factor)+" must be < 1 and has been set to 1");
    damping_factor = 1;
  }
}

Border::Border(std::pair<double, double> const & boundary_position,
	       std::pair<double, double> const & boundary_size,
	       double const in_damping_factor) :
  Border(boundary_position.first, boundary_size.first,
	 boundary_position.second, boundary_size.second,
	 in_damping_factor) {}

void Border::Collide(ParticleContainer & particle_container) {
  for(Particle & particle : particle_container) {
    auto CheckAxis =
      [](double & position, double & velocity, double const radius,
	 double const sboundary, double const lboundary, double const damping) {
	if(position+radius > sboundary+lboundary) {
	  position = sboundary+lboundary-radius;
	  velocity *= -damping;
	} else if(position-radius < sboundary) {
	  position = sboundary+radius;
	  velocity *= -damping;
	}
      };
    CheckAxis(particle.pos_x, particle.vel_x, particle.radius, xmin, xmax, damping_factor);
    CheckAxis(particle.pos_y, particle.vel_y, particle.radius, ymin, ymax, damping_factor);
  }
}
