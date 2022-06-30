# Basic parameters; check that these match your project / environment
cmake_minimum_required(VERSION 3.8)

set(PROJECT_NAME MarbleMaze)

project(${PROJECT_NAME})

#set(PROJECT_SOURCES src/game/MarbleMaze.cpp include/game/MarbleMaze.hpp)

set(GAME_SOURCES
	"MarbleMaze.cpp"

	#".cpp"

	"Constants.cpp"
)

set(PHYSICSENGINE_SOURCE
	"Collisions.cpp"
	"Constraints.cpp"
	"Shape.cpp"
	"RigidBody.cpp"

	"PhysicsEngineMath.cpp"

	"PhysicsEngine.cpp"
)

set(PROJECT_DISTRIBS LICENSE README.md)

list(TRANSFORM GAME_SOURCES PREPEND src/game/)
list(TRANSFORM PHYSICSENGINE_SOURCE PREPEND src/physicsengine/)

set(PROJECT_SOURCES ${PHYSICSENGINE_SOURCE};${GAME_SOURCES})
#list(APPEND PROJECT_SOURCES "Assets.cpp")

#set(ASSET_OUTPUTS "Assets.hpp" "Assets.cpp")
set(ASSET_DEPENDS "Assets.yml")

# Build configuration; approach this with caution!
if(MSVC)
  add_compile_options("/W4" "/wd4244" "/wd4324")
else()
  add_compile_options("-Wall" "-Wextra" "-Wdouble-promotion")
endif()
find_package (32BLIT CONFIG REQUIRED PATHS ../32blit-sdk)

blit_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

include_directories(${PROJECT_SOURCE_DIR}/include/physicsengine)
include_directories(${PROJECT_SOURCE_DIR}/include/game)
include_directories(${PROJECT_SOURCE_DIR}/include/external)

blit_assets_yaml(${PROJECT_NAME} ${ASSET_DEPENDS})
blit_metadata(${PROJECT_NAME} metadata.yml)
add_custom_target(flash DEPENDS ${PROJECT_NAME}.flash)

# setup release packages
install(FILES ${PROJECT_DISTRIBS} DESTINATION .)
set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY OFF)
set(CPACK_GENERATOR "ZIP" "TGZ")
include(CPack)
