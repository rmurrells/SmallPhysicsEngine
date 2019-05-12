#ifndef SIMULATIONBUILDER_HPP
#define SIMULATIONBUILDER_HPP

#include "Simulation.hpp"

class SimulationBuilder {
public:
  Simulation Build() const;
  SimulationBuilder & SetWindowSize(int const in_width, int const in_height);
  SimulationBuilder & SetBackgroundColor(SDL_Color const & in_background_color);
  SimulationBuilder & SetParticleMotionDamping(double const in_particle_motion_damping);
  SimulationBuilder & SetG(double const in_G);
  SimulationBuilder & SetParticleCR(double const in_particle_cr);
  SimulationBuilder & SetImmovableCR(double const in_immovable_cr);
  SimulationBuilder & SetBorderCR(double const in_border_cr);
  SimulationBuilder & SetMouseAccel(double const in_mouse_acceleration);
private:
  int width = 800;
  int height = 600;
  SDL_Color background_color = {255, 255, 255, 255};
  double particle_motion_damping{1};
  double G{0};
  double particle_cr{1};
  double immovable_cr{1};
  double border_cr{1};
  double mouse_acceleration{0};
};

#endif
