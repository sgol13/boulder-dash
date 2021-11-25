# Szymon Golebiowski
# Boulder Dash

cmake_minimum_required(VERSION 3.10.2)

project(boulder-dash)

#set c++ standard (C++14 is required to build the project)
set (CMAKE_CXX_STANDARD 14)

#set g++ compilation flags
set(CMAKE_CXX_FLAGS "-Wall -Wconversion -Wextra -Wshadow -Werror -g")

# relative paths to resources directory
set(RESOURCES_DIR "../res/")
set(GRAPHIC_RESOURCES_DIR "${RESOURCES_DIR}textures/")
set(FONT_RESOURCES_DIR "${RESOURCES_DIR}fonts/")
set(AUDIO_RESOURCES_DIR "${RESOURCES_DIR}sounds/")
set(LEVEL_RESOURCES_DIR "${RESOURCES_DIR}levels/")

add_definitions(-DBD_GRAPHIC_RESOURCES_DIR="${GRAPHIC_RESOURCES_DIR}")
add_definitions(-DBD_FONT_RESOURCES_DIR="${FONT_RESOURCES_DIR}")
add_definitions(-DBD_AUDIO_RESOURCES_DIR="${AUDIO_RESOURCES_DIR}")
add_definitions(-DBD_LEVEL_RESOURCES_DIR="${LEVEL_RESOURCES_DIR}")

# list of source files
set(sources

src/main.cpp

# game components
src/game_components/Engine.cpp
src/game_components/Video.cpp
src/game_components/Audio.cpp
src/game_components/Input.cpp
src/game_components/Game.cpp
src/game_components/Menu.cpp
src/game_components/Ranking.cpp

# map elements
src/map_elements/MapElement.cpp
src/map_elements/Exit.cpp
src/map_elements/Moveable.cpp
src/map_elements/Boulder.cpp
src/map_elements/Player.cpp
src/map_elements/Flyable.cpp

# other files
src/Level.cpp
)

add_executable(game ${sources})

# path to header files
target_include_directories(game PRIVATE include)

# link SFML modules
target_link_libraries(game sfml-graphics sfml-audio sfml-window sfml-system)