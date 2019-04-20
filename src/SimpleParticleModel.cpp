#include "SimpleParticleModel.hpp"
#include <limits>

SimpleParticleModel::SimpleParticleModel(int const fps,
					 std::pair<int, int> const & boundary_position,
					 std::pair<int, int> const & boundary_size) :
  move_factor{60./fps},
  boundary_x{boundary_position.first}, boundary_y{boundary_position.second},
  boundary_w{boundary_size.first}, boundary_h{boundary_size.second} {}

void SimpleParticleModel::MoveParticles(ParticleContainer & particle_container) {
  std::vector<Particle> & particles{particle_container.GetParticles()};
  for(auto it = particles.begin(); it != particles.end(); ++it) {
    Particle & particle = *it;
    particle.pos_x += particle.vel_x*move_factor;
    particle.pos_y += particle.vel_y*move_factor;
    BoundaryCollision(*it);
  }
}

void SimpleParticleModel::BoundaryCollision(Particle & particle) {
  auto CheckAxis =
    [](double & position, double & velocity, double const radius, double const sboundary, double const lboundary) {
      if(velocity > 0 && position+radius > sboundary+lboundary) {
	position = sboundary+lboundary-radius;
	velocity *= -1;
      } else if(position-radius < sboundary) {
	position = sboundary+radius;
	velocity *= -1;
      }
    };
  CheckAxis(particle.pos_x, particle.vel_x, particle.radius, boundary_x, boundary_w);
  CheckAxis(particle.pos_y, particle.vel_y, particle.radius, boundary_y, boundary_h);
}
