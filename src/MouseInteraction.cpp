#include "MouseInteraction.hpp"
#include "Math.hpp"

void MouseInteraction::Radial(ParticleContainer & particle_container, MouseState const & mouse_state, double const speed) {
  if((!mouse_state.left && !mouse_state.right)) return; 
  auto UpdateParticles =
    [&](double const factor) {
      for(Particle & particle : particle_container) {
	double const dist_x{particle.pos_x - mouse_state.x};
	double const dist_y{particle.pos_y - mouse_state.y};
	double const dist{Math::Magnitude(dist_x, dist_y)};
	if(dist > 0) {
	  particle.vel_x += dist_x/dist*factor;
	  particle.vel_y += dist_y/dist*factor;
	}
      }
    };
  if(mouse_state.left) UpdateParticles(-speed);
  else UpdateParticles(speed);
}
