#include "boulder-dash2/map_elements/Exit.hpp"

bd2::Exit::Exit(Type _type, const MapCoordinates &_position)
    : MapElement(_type, _position) {}

void bd2::Exit::loadTextures(const ResourceHandler<sf::Texture> &textures_handler) {

    basic_texture_ = textures_handler[resources::Textures::WALL];
    opened_exit_texture_ = textures_handler[resources::Textures::EXIT];

    startAnimation(*basic_texture_);
}

void bd2::Exit::openDoor() { startAnimation(*opened_exit_texture_); }