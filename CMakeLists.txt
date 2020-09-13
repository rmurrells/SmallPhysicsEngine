cmake_minimum_required(VERSION 3.16)
project(SmallPhysicsEngine VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")

	if(NOT CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
		message(FATAL_ERROR "MSVC required on ${CMAKE_SYSTEM_NAME}.")
	endif()
	add_compile_options(/EHsc /W4)

	find_path(SDL2_DIR NAMES include/SDL.h PATHS ${CMAKE_SOURCE_DIR}/* NO_DEFAULT_PATHS)
	if(NOT SDL2_DIR)
		message(FATAL_ERROR "Could not find SDL2.")
	endif()
	set(SDL2_INCLUDE_DIRS ${SDL2_DIR}/include)

	if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
		set(SDL2_LIBDIR "${SDL2_DIR}/lib/x64")
	else ()
		set(SDL2_LIBDIR "${SDL2_DIR}/lib/x86")
	endif ()
	set(SDL2_LIBRARIES "${SDL2_LIBDIR}/SDL2.lib;${SDL2_LIBDIR}/SDL2main.lib")
	
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin" OR CMAKE_SYSTEM_NAME STREQUAL "Linux")

	if(NOT CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND NOT CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "GNU" AND NOT CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
		message(FATAL_ERROR "GCC compatible compiler required on ${CMAKE_SYSTEM_NAME}.")
	endif()
	find_package(SDL2 REQUIRED)
	if(NOT CMAKE_BUILD_TYPE)
  		set(CMAKE_BUILD_TYPE Release)
	endif()
	set(CMAKE_CXX_FLAGS "-Wall")
	set(CMAKE_CXX_FLAGS_DEBUG "-g")
	set(CMAKE_CXX_FLAGS_RELEASE "-O2")
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Release)
else()
	message(FATAL_ERROR "${CMAKE_SYSTEM_NAME} not supported.")
endif()

set(INC_DIR ${CMAKE_SOURCE_DIR}/inc)
add_subdirectory(src)

set(TARGETS
	all_move
	all_move_interactive
	different_masses
	single_move
	single_move_gravity
	#view_texture
)

foreach(TARGET ${TARGETS})
	add_executable(${TARGET} ${CMAKE_SOURCE_DIR}/src/exec/${TARGET}.cpp)
	target_include_directories(${TARGET} PUBLIC ${INC_DIR})
	target_link_libraries(${TARGET} PUBLIC src ${SDL2_LIBRARIES})
endforeach()

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	list(GET TARGETS 0 FIRST)
	add_custom_command(TARGET ${FIRST} PRE_BUILD
		COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${SDL2_LIBDIR}/SDL2.dll" "${CMAKE_BINARY_DIR}/$<CONFIG>/"
	)
endif()