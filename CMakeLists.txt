cmake_minimum_required(VERSION 3.18)
project(SmallPhysicsEngine VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()
set(CMAKE_CXX_FLAGS "-Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-padded -Wno-reserved-id-macro -Wno-implicit-fallthrough -Wno-documentation")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

find_package(SDL2)
set(BIN ${CMAKE_BINARY_DIR}/bin)
set(INC_DIR ${CMAKE_SOURCE_DIR}/inc)
add_subdirectory(src)

set(TARGETS
	all_move
	all_move_interactive
	different_masses
	single_move
	single_move_gravity
	view_texture
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN})

foreach(TARGET ${TARGETS})
	       add_executable(${TARGET} ${CMAKE_SOURCE_DIR}/src/exec/${TARGET}.cpp)
	       target_include_directories(${TARGET} PUBLIC ${INC_DIR})
	       target_link_libraries(${TARGET} PUBLIC src ${SDL2_LIBRARIES})
endforeach()
