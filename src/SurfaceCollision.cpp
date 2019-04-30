#include "SurfaceCollision.hpp"
#include "Math.hpp"

void SurfaceCollision::UpdateVelocity(double & vel_x, double & vel_y,
				      double const norm_x, double const norm_y,
				      double const cr) {
  double const dp{vel_x*norm_x + vel_y*norm_y};
  vel_x -= (1+cr)*dp*norm_x;
  vel_y -= (1+cr)*dp*norm_y;
}
