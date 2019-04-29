#include "SimpleParticleCollider.hpp"
#include <cmath>
#include "Math.hpp"

SimpleParticleCollider::SimpleParticleCollider(double const in_coefficient_of_restitution) :
  coefficient_of_restitution{in_coefficient_of_restitution} {}

void SimpleParticleCollider::Collide(ParticleContainer & particles) const {
  for(auto begin{particles.begin()}, it{begin}, end{particles.end()}; it != end; ++it) {
    for(auto it2{begin}; it2 != end; ++it2) {
      if(it2 == it) continue;
      CollideParticlePair(*it2, *it);
    }
  }
}

void SimpleParticleCollider::HandleParticleSamePosition(Particle & particle1, Particle & particle2) const {
  double const mag1{Math::Magnitude(particle1.vel_x, particle1.vel_y)};
  double const mag2{Math::Magnitude(particle2.vel_x, particle2.vel_y)};
  double const radius_sum{particle1.radius + particle2.radius};
  auto UpdateParticle =
    [](Particle & particle, double const dist, double const mag) {
      particle.pos_x -= dist*particle.vel_x/mag;
      particle.pos_y -= dist*particle.vel_y/mag;      
    };
  if(mag1 > 0 && mag2 > 0) {
    double const cos_theta{std::acos(Math::DotProduct(particle1.vel_x, particle1.vel_y,
						      particle2.vel_x, particle2.vel_y)/(mag1*mag2))};
    if(cos_theta-1 < std::numeric_limits<double>::epsilon()) {
      if(mag1 > mag2) UpdateParticle(particle1, radius_sum, mag1);
      else UpdateParticle(particle2, radius_sum, mag2);
    } else {
      double const dist{radius_sum/(2*std::sin(cos_theta/2))};
      UpdateParticle(particle1, dist, mag1);
      UpdateParticle(particle2, dist, mag2);
    }
  } else if(mag1 > mag2) UpdateParticle(particle1, radius_sum, mag1);
  else if(mag2 > mag1) UpdateParticle(particle2, radius_sum, mag2);
  else {
    particle1.pos_x -= radius_sum/2;
    particle2.pos_x += radius_sum/2;
  }
}

void SimpleParticleCollider::UpdateParticleVelocity(Particle & particle1, Particle & particle2) const {
  double const dp1{Math::DotProduct(particle1.vel_x-particle2.vel_x, particle1.vel_y-particle2.vel_y,
				    particle1.pos_x-particle2.pos_x, particle1.pos_y-particle2.pos_y)};
  double const dp2{Math::DotProduct(particle2.vel_x-particle1.vel_x, particle2.vel_y-particle1.vel_y,
				    particle2.pos_x-particle1.pos_x, particle2.pos_y-particle1.pos_y)};
  double const distx{particle1.pos_x-particle2.pos_x};
  double const disty{particle1.pos_y-particle2.pos_y};
  double const distsq{distx*distx + disty*disty};
  auto UpdateVelocity =
    [distsq](double & new_velocity, double const this_mass, double const other_mass,
	     double const dp, double const translation, double const cr) {
      new_velocity -= (1+cr)*other_mass/(this_mass+other_mass)*dp/distsq*translation;
    };
  UpdateVelocity(particle1.vel_x, particle1.mass, particle2.mass, dp1, distx, coefficient_of_restitution);
  UpdateVelocity(particle1.vel_y, particle1.mass, particle2.mass, dp1, disty, coefficient_of_restitution);
  UpdateVelocity(particle2.vel_x, particle2.mass, particle1.mass, dp2, distx*-1, coefficient_of_restitution);
  UpdateVelocity(particle2.vel_y, particle2.mass, particle1.mass, dp2, disty*-1, coefficient_of_restitution);
}

void SimpleParticleCollider::CollideParticlePair(Particle & particle1, Particle & particle2) const {
  double const distx{particle1.pos_x-particle2.pos_x};
  double const disty{particle1.pos_y-particle2.pos_y};
  double const dist{std::sqrt(distx*distx + disty*disty)};
  double const radius_sum{particle1.radius + particle2.radius};
  if(dist >= radius_sum) return;
  if(dist < std::numeric_limits<double>::epsilon()) HandleParticleSamePosition(particle1, particle2);
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
