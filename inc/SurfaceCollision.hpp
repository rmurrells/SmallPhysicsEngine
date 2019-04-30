#ifndef SURFACECOLLISION_HPP
#define SURFACECOLLISION_HPP

namespace SurfaceCollision {
  void UpdateVelocity(double & vel_x, double & vel_y,
		      double const norm_x, double const norm_y,
		      double const cr);
}

#endif
