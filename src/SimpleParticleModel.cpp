#include "SimpleParticleModel.hpp"
#include <cmath>
#include "Utility.hpp"

namespace {

  void MoveParticles(ParticleContainer & particles) {
    for(Particle & particle : particles) {
      particle.pos_x += particle.vel_x;
      particle.pos_y += particle.vel_y;
    }
  }

  void HandleParticleSamePosition(Particle & particle1, Particle & particle2, double const radius_sum) {
    double const mag1{Utility::Magnitude(particle1.vel_x, particle1.vel_y)};
    double const mag2{Utility::Magnitude(particle2.vel_x, particle2.vel_y)};
    auto UpdateParticle =
      [](Particle & particle, double const dist, double const mag) {
	particle.pos_x -= dist*particle.vel_x/mag;
	particle.pos_y -= dist*particle.vel_y/mag;      
      };
    if(mag1 > 0 && mag2 > 0) {
      double const cos_theta{std::acos(Utility::DotProduct(particle1.vel_x, particle1.vel_y,
							   particle2.vel_x, particle2.vel_y)/(mag1*mag2))};
      if(cos_theta-1 < std::numeric_limits<double>::epsilon()) {
	if(mag1 > mag2) UpdateParticle(particle1, radius_sum, mag1);
	else UpdateParticle(particle2, radius_sum, mag2);
      } else {
	double const dist{radius_sum/(2*std::sin(cos_theta/2))};
	UpdateParticle(particle1, dist, mag1);
	UpdateParticle(particle2, dist, mag2);
      }
    } else {
      if(mag1 > mag2) UpdateParticle(particle1, radius_sum, mag1);
      else UpdateParticle(particle2, radius_sum, mag2);
    }
  }

  void UpdateParticleVelocity(Particle & particle1, Particle & particle2) {
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

  void CollideParticlePair(Particle & particle1, Particle & particle2) {
    double const distx{particle1.pos_x-particle2.pos_x};
    double const disty{particle1.pos_y-particle2.pos_y};
    double const dist{std::sqrt(distx*distx + disty*disty)};
    double const radius_sum{particle1.radius + particle2.radius};
    if(dist >= radius_sum) return;
    if(dist < std::numeric_limits<double>::epsilon()) HandleParticleSamePosition(particle1, particle2, radius_sum);
    else {
      double const split_distx{(radius_sum*distx/dist - distx)/2};
      double const split_disty{(radius_sum*disty/dist - disty)/2};
      particle1.pos_x += split_distx;
      particle1.pos_y += split_disty;
      particle2.pos_x -= split_distx;
      particle2.pos_y -= split_disty;
    }
    UpdateParticleVelocity(particle1, particle2);
  }

  void BoundaryCollision(Particle & particle, Border const & border) {
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
    CheckAxis(particle.pos_x, particle.vel_x, particle.radius, border.xmin, border.xmax);
    CheckAxis(particle.pos_y, particle.vel_y, particle.radius, border.ymin, border.ymax);
  }

  void ParticleCollisions(ParticleContainer & particles, Border const & border) {
    for(auto it = particles.begin(); it != particles.end(); ++it) {
      for(auto it2 = particles.begin(); it2 != particles.end(); ++it2) {
	if(it2 == it) continue;
	CollideParticlePair(*it2, *it);
      }
      BoundaryCollision(*it, border);
    }
  }

}

void SimpleParticleModel::Run(ParticleContainer & particles, Border const & border) {
  MoveParticles(particles);
  ParticleCollisions(particles, border);
}
