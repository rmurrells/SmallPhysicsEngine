#include "ImmovableParticleCollider.hpp"
#include <cmath>
#include "Math.hpp"

ImmovableParticleCollider::ImmovableParticleCollider(double const in_coefficient_of_restitution) :
  coefficient_of_restitution{in_coefficient_of_restitution} {}

void ImmovableParticleCollider::Collide(ParticleContainer & particles,
					ImmovableContainer const & immovables) const {
  for(Particle & particle : particles) {
    for(Immovable const & immovable : immovables) {
      CollideParticleWImmovable(particle, immovable);
    }
  }
}

void ImmovableParticleCollider::UpdateParticleVelocity(Particle & particle,
						    Immovable const & immovable) const {
  double const distx{immovable.pos_x - particle.pos_x};
  double const disty{immovable.pos_y - particle.pos_y};
  double const mag{Math::Magnitude(distx, disty)};
  double const dp{(particle.vel_x*distx + particle.vel_y*disty)/mag};
  particle.vel_x -= 2*dp*distx/mag;
  particle.vel_y -= 2*dp*disty/mag;
}

void ImmovableParticleCollider::HandleParticleSamePosition(Particle & particle,
							Immovable const & immovable) const {
  double const mag{Math::Magnitude(particle.vel_x, particle.vel_y)};
  double const radius_sum{particle.radius + immovable.radius};
  if(mag > 0) {
    particle.pos_x += radius_sum*particle.vel_x/mag;
    particle.pos_y += radius_sum*particle.vel_y/mag;    
  } else particle.pos_x += radius_sum;
}

void ImmovableParticleCollider::CollideParticleWImmovable(Particle & particle,
						       Immovable const & immovable) const {
  double const distx{particle.pos_x-immovable.pos_x};
  double const disty{particle.pos_y-immovable.pos_y};
  double const dist{std::sqrt(distx*distx + disty*disty)};
  double const radius_sum{immovable.radius + particle.radius};
  if(dist >= radius_sum) return;
  if(dist < std::numeric_limits<double>::epsilon()) HandleParticleSamePosition(particle, immovable);
  else {
    particle.pos_x += radius_sum*distx/dist - distx;
    particle.pos_y += radius_sum*disty/dist - disty;
  }
  UpdateParticleVelocity(particle, immovable);
}
