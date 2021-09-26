cmake_minimum_required(VERSION 3.10.2)

project(boulder-dash2)

#set c++ standard (C++14 is required to built the project)
set (CMAKE_CXX_STANDARD 14)

#set g++ compilation flags
set(CMAKE_CXX_FLAGS "-Wall -Wconversion -Wextra -Wshadow")

# relative paths to resources directory
set(RESOURCES_DIR "../res/")
set(GRAPHIC_RESOURCES_DIR "${RESOURCES_DIR}textures/")
set(FONT_RESOURCES_DIR "${RESOURCES_DIR}fonts/")
set(LEVEL_RESOURCES_DIR "${RESOURCES_DIR}levels/")

add_definitions(-DBD2_GRAPHIC_RESOURCES_DIR="${GRAPHIC_RESOURCES_DIR}")
add_definitions(-DBD2_FONT_RESOURCES_DIR="${FONT_RESOURCES_DIR}")
add_definitions(-DBD2_LEVEL_RESOURCES_DIR="${LEVEL_RESOURCES_DIR}")

# list of source files
set(sources
src/main.cpp

# game components
#src/game_components/Engine.cpp
#src/game_components/Video.cpp
#src/game_components/Game.cpp
#src/game_components/Input.cpp

# map elements
#src/map_elements/MapElement.cpp
#src/map_elements/Moveable.cpp
#src/map_elements/Animatable.cpp

# other files
src/Level.cpp
)

add_executable(game ${sources})

# path to header files
target_include_directories(game PRIVATE include)

# link SFML modules
target_link_libraries(game sfml-graphics sfml-audio sfml-window sfml-system)