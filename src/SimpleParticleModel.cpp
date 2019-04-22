#include "SimpleParticleModel.hpp"
#include <cmath>
#include "Utility.hpp"

SimpleParticleModel::SimpleParticleModel(int const fps,
					 std::pair<int, int> const & boundary_position,
					 std::pair<int, int> const & boundary_size) :
  move_factor{60./fps},
  boundary_x{boundary_position.first}, boundary_y{boundary_position.second},
  boundary_w{boundary_size.first}, boundary_h{boundary_size.second} {}

void SimpleParticleModel::Run(ParticleContainer & particles) {
  MoveParticles(particles);
  ParticleCollisions(particles);
}

void SimpleParticleModel::MoveParticles(ParticleContainer & particles) {
  for(Particle & particle : particles) {
    particle.pos_x += particle.vel_x*move_factor;
    particle.pos_y += particle.vel_y*move_factor;
  }
}

void SimpleParticleModel::UpdateParticleVelocity(Particle & particle1, Particle & particle2) {
  double const dp1{Utility::DotProduct(particle1.vel_x-particle2.vel_x, particle1.vel_y-particle2.vel_y,
				       particle1.pos_x-particle2.pos_x, particle1.pos_y-particle2.pos_y)};
  double const dp2{Utility::DotProduct(particle2.vel_x-particle1.vel_x, particle2.vel_y-particle1.vel_y,
				       particle2.pos_x-particle1.pos_x, particle2.pos_y-particle1.pos_y)};
  double const distx{particle1.pos_x-particle2.pos_x};
  double const disty{particle1.pos_y-particle2.pos_y};
  double const distsq{distx*distx + disty*disty};
  auto UpdateVelocity =
    [distsq](double & new_velocity, double const this_mass, double const other_mass,
	     double const dp, double const translation) {
      new_velocity -= 2*other_mass/(this_mass+other_mass)*dp/distsq*translation;
    };
  UpdateVelocity(particle1.vel_x, particle1.mass, particle2.mass, dp1, distx);
  UpdateVelocity(particle1.vel_y, particle1.mass, particle2.mass, dp1, disty);
  UpdateVelocity(particle2.vel_x, particle2.mass, particle1.mass, dp2, -1*distx);
  UpdateVelocity(particle2.vel_y, particle2.mass, particle1.mass, dp2, -1*disty);
}

void SimpleParticleModel::ParticleCollision(Particle & particle1, Particle & particle2) {
  double distx{particle1.pos_x-particle2.pos_x};
  double disty{particle1.pos_y-particle2.pos_y};
  double dist{std::sqrt(distx*distx + disty*disty)};
  double const radius_sum{particle1.radius + particle2.radius};
  if(dist >= radius_sum) return;
  double const split_distx{(radius_sum*distx/dist - distx)/2};
  double const split_disty{(radius_sum*disty/dist - disty)/2};
  particle1.pos_x += split_distx;
  particle1.pos_y += split_disty;
  particle2.pos_x -= split_distx;
  particle2.pos_y -= split_disty;
  UpdateParticleVelocity(particle1, particle2);
}

void SimpleParticleModel::ParticleCollisions(ParticleContainer & particles) {
  for(auto it = particles.begin(); it != particles.end(); ++it) {
    for(auto it2 = particles.begin(); it2 != particles.end(); ++it2) {
      if(it2 == it) continue;
      ParticleCollision(*it2, *it);
    }
    BoundaryCollision(*it);
  }
}

void SimpleParticleModel::BoundaryCollision(Particle & particle) {
  auto CheckAxis =
    [](double & position, double & velocity,
       double const radius, double const sboundary, double const lboundary) {
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
