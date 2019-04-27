#include "Simulation.hpp"

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

}

int main() {
  Simulation simulation{1, 0.9, 0.9, 0.1};
  simulation.SetBackgroundColor(0, 0, 0);
  auto const [width, height] = simulation.GetWindowSize();
  double const radius{4}; double const mass{1}; 
  int const nj = 30;
  int const ni = 34;
  SDL_Color color{255, 0, 0, 255};
  for(int j{1}; j < nj; ++j) {
    for(int i{1}; i < ni; ++i) {
      double const pos_x{i*static_cast<double>(width)/ni};
      double const pos_y{j*static_cast<double>(height)/nj};
      simulation.AddParticle(pos_x, pos_y, 0, 0, radius, mass, color);
      IncrementColor(color);
    }
  }
  simulation.Run();
}