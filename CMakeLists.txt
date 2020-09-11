cmake_minimum_required(VERSION 3.18)
project(SmallPhysicsEngine VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	if(NOT CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
		message(FATAL_ERROR "MSVC required on ${CMAKE_SYSTEM_NAME}.")
	endif()
	add_compile_options(/EHsc /W4)

	set(SDL2_DIR ${CMAKE_SOURCE_DIR}/SDL2)
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
	set(CMAKE_CXX_FLAGS "-Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-padded -Wno-reserved-id-macro -Wno-implicit-fallthrough -Wno-documentation")
	set(CMAKE_CXX_FLAGS_DEBUG "-g")
	set(CMAKE_CXX_FLAGS_RELEASE "-O2")
endif()

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
foreach(TARGET ${TARGETS})
	add_executable(${TARGET} ${CMAKE_SOURCE_DIR}/src/exec/${TARGET}.cpp)
	if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
		add_custom_command(TARGET ${TARGET} POST_BUILD
			COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${SDL2_LIBDIR}/SDL2.dll" "${CMAKE_BINARY_DIR}/$<CONFIG>/"
		)
	endif()
	target_include_directories(${TARGET} PUBLIC ${INC_DIR})
	target_link_libraries(${TARGET} PUBLIC src ${SDL2_LIBRARIES})
endforeach()
