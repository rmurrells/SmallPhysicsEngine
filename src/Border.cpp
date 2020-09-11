#include "Border.hpp"
#include "Utility.hpp"
#include "SurfaceCollision.hpp"

Border::Border(double const in_xmin, double const in_xmax,
	       double const in_ymin, double const in_ymax,
	       double const in_coefficient_of_restitution) :
  xmin{in_xmin}, xmax{in_xmax}, ymin{in_ymin}, ymax{in_ymax}, coefficient_of_restitution{in_coefficient_of_restitution} {
  if(coefficient_of_restitution > 1) {
    Utility::Warning("Chosen Border coefficient of restitution: "+std::to_string(coefficient_of_restitution)+" must be <= 1 and has been set to 1");
    coefficient_of_restitution = 1;
  }
}

Border::Border(std::pair<double, double> const & boundary_position,
	       std::pair<double, double> const & boundary_size,
	       double const in_coefficient_of_restitution) :
  Border(boundary_position.first, boundary_size.first,
	 boundary_position.second, boundary_size.second,
	 in_coefficient_of_restitution) {}

void Border::Collide(ParticleContainer & particle_container) {
  for(Particle & particle : particle_container) {
    auto CheckAxis =
      [&particle, this](double & position, double const sboundary, double const lboundary,
			bool const xaxis) {
	if(position+particle.radius > sboundary+lboundary) {
	  position = sboundary+lboundary-particle.radius;
	  SurfaceCollision::UpdateVelocity(particle.vel_x, particle.vel_y,
					   -int(xaxis), -int(!xaxis), coefficient_of_restitution);
	} else if(position-particle.radius < sboundary) {
	  position = sboundary+particle.radius;
	  SurfaceCollision::UpdateVelocity(particle.vel_x, particle.vel_y,
					   xaxis, !xaxis, coefficient_of_restitution);	  
	}
      };
    CheckAxis(particle.pos_x, xmin, xmax, true);
    CheckAxis(particle.pos_y, ymin, ymax, false);
  }
}
