# Small Physics Engine

A simple 2D ball simulation written in C++ using SDL.

# Instructions

All platforms require [CMake](https://cmake.org/download/).

## Windows

Requires [Visual Studio 2019](https://visualstudio.microsoft.com/).

Download the latest SDL2 develoment libraries for Visual Studio (SDL2-devel-\<version\>-VC.zip) from https://www.libsdl.org/download-2.0.php, place the SDL2-\<version\> directory found inside into the top level of the repository.

## Unix-like

Requires [GCC](https://gcc.gnu.org/) or [Clang](https://clang.llvm.org/).

Download the latest SDL2 development libraries using an appropriate package manager:
* apt - libsdl2-dev
* brew - sdl2
or [download and build from source](https://www.libsdl.org/download-2.0.php).

# Installation

Enter the top level of the repository and run the following:
```
mkdir build
cd build
cmake ..
cmake --build . --config release
```

This will create an an executable directory called Release that contains four simulation executables to run. The escape key can be used to close a simulation. Left and right click will attract and repel balls to the cursor location respectively for the all_move_interactive simulation.
