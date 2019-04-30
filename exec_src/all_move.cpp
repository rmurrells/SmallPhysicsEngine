#include "SimulationBuilder.hpp"

namespace {
  
  void IncrementColor(SDL_Color & color) {
    static int sum{0};
    int const max_color{255};
    switch(sum/max_color) {
    case 0:
      ++color.g;
      break;
    case 1:
      --color.r;
      break;
    case 2:
      ++color.b;
      break;
    case 3:
      --color.g;
      break;
    default:
      std::cout << "Error, switch exceeds 4: " << sum/max_color << '\n';
    }
    ++sum;
  }

  std::pair<double, double> SetCircleVelocity(double const pos_x, double const pos_y,
					      double const center_x, double const center_y,
					      double const speed) {
    double const dist_x{pos_x - center_x};
    double const dist_y{pos_y - center_y};
    double const mag{std::sqrt(dist_x*dist_x+dist_y*dist_y)};
    return {speed*dist_x/mag, speed*dist_y/mag};
  }
  
}

int main() {
  Simulation simulation{SimulationBuilder()
			.SetBackgroundColor({0, 0, 0, 255})
			.Build()};
  auto const [width, height] = simulation.GetWindowSize();
  double const radius{4}; double const mass{1}; 
  int const nj = 30;
  int const ni = 34;
  SDL_Color color{255, 0, 0, 255};
  for(int j{1}; j < nj; ++j) {
    for(int i{1}; i < ni; ++i) {
      double const pos_x{i*static_cast<double>(width)/ni};
      double const pos_y{j*static_cast<double>(height)/nj};
      if(static_cast<int>(pos_x) != width/2 || static_cast<int>(pos_y) != height/2) {
	auto const [vel_x, vel_y] = SetCircleVelocity(pos_x, pos_y, width/2, height/2, -std::sqrt(2));
	simulation.AddParticle(pos_x, pos_y, vel_x, vel_y, radius, mass, color);
      }
      IncrementColor(color);
    }
  }
  simulation.Run();
}
