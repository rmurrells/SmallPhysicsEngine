add_library(
	src OBJECT
	Border.cpp
	Gravity.cpp
	Immovable.cpp
	ImmovableParticleCollider.cpp
	InputHandler.cpp
	Math.cpp
	MouseInteraction.cpp
	MouseState.cpp
	Particle.cpp
	ParticleMover.cpp
	SDLBase.cpp
	SDLRenderer.cpp
	SDLTexture.cpp
	SDLWindow.cpp
	SimpleParticleCollider.cpp
	Simulation.cpp
	SimulationBuilder.cpp
	SurfaceCollision.cpp
	Utility.cpp	
)

target_include_directories(src PUBLIC
                           ${INC_DIR}
			   ${SDL2_INCLUDE_DIRS}
			   )
