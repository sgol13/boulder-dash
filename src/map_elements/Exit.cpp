// Szymon Golebiowski
// Boulder Dash 2, 2021

#include "boulder-dash2/map_elements/Exit.hpp"

bd2::Exit::Exit(Type _type, const MapCoordinates &_map_position)
    : MapElement(_type, _map_position), is_open(false) {}

void bd2::Exit::loadTextures(const ResourceHandler<sf::Texture> &textures_handler) {

    basic_texture_ = textures_handler[resources::Textures::WALL];
    opened_exit_texture_ = textures_handler[resources::Textures::EXIT];

    startAnimation(*basic_texture_);
}

void bd2::Exit::openDoor() {

    is_open = true;
    startAnimation(*opened_exit_texture_);
}

bool bd2::Exit::isOpen() { return is_open; }