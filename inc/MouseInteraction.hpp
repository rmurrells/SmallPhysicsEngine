#ifndef MOUSEINTERACTION_HPP
#define MOUSEINTERACTION_HPP

#include "MouseState.hpp"
#include "ParticleContainer.hpp"

struct MouseInteraction {
  MouseInteraction(double const in_mouse_acceleration = 0);
  void Radial(ParticleContainer & particle_container, MouseState const & mouse_state);
  double mouse_acceleration;
};

#endif
