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
      --color.b;
      break;
    case 2:
      ++color.r;
      break;
    case 3:
      --color.g;
      break;
    default:
      std::cout << "Error, switch exceeds 4: " << sum/max_color << '\n';
    }
    ++sum;
  }

}

int main(int, char*[]) {
  double const cr{0.5};
  Simulation simulation{SimulationBuilder()
			.SetBackgroundColor({0, 0, 0, 255})
			.SetParticleCR(cr)
			.SetImmovableCR(cr)
			.SetBorderCR(cr)
			.SetMouseAccel(0.8)
			.Build()};
  auto const [width, height] = simulation.GetWindowSize();
  double const radius{4}; double const mass{1}; 
  int const nj = 30;
  int const ni = 34;
  SDL_Color color{0, 0, 255, 255};
  for(int j{1}; j < nj; ++j) {
    for(int i{1}; i < ni; ++i) {
      double const pos_x{i*static_cast<double>(width)/ni};
      double const pos_y{j*static_cast<double>(height)/nj};
      simulation.AddParticle(pos_x, pos_y, 0, 0, radius, mass, color);
      IncrementColor(color);
    }
  }
  simulation.AddImmovable(static_cast<double>(width/4), static_cast<double>(height/4), 50, {125, 125, 125, 255});
  simulation.AddImmovable(static_cast<double>(3*width/4), static_cast<double>(height/4), 50, {125, 125, 125, 255});
  simulation.AddImmovable(static_cast<double>(width/4), static_cast<double>(3*height/4), 50, {125, 125, 125, 255});
  simulation.AddImmovable(static_cast<double>(3*width/4), static_cast<double>(3*height/4), 50, {125, 125, 125, 255});
  simulation.Run();
  return 0;
}
