cmake_minimum_required(VERSION 3.10.2)

project(boulder-dash2)


# relative path to resources directory
add_definitions(-DABC="../res/")

# list of source files
set(sources
src/main.cpp

# namespace game

# namespace map_elements

# namespace menu

# other classes
)

add_executable(game ${sources})

# path to header files
target_include_directories(game PRIVATE include)

# link SFML modules
target_link_libraries(game sfml-graphics sfml-audio sfml-window sfml-system)