#include "boulder-dash2/map_elements/MapElement.hpp"

bool bd2::MapElement::Compare::operator()(const std::weak_ptr<MapElement> el1,
                                          const std::weak_ptr<MapElement> el2) {

    auto p1 = el1.lock();
    auto p2 = el2.lock();

    // if one of the pointers is expired
    if (p1 && !p2)
        return false;

    if (!p1 && p2)
        return true;

    if (!p1 && !p2)
        return true;

    // if both pointers are not expired
    auto it1 = std::find(type_layers.begin(), type_layers.end(), p1->type_);
    auto it2 = std::find(type_layers.begin(), type_layers.end(), p2->type_);

    return it1 < it2;
}

const std::vector<bd2::MapElement::Type> bd2::MapElement::Compare::type_layers = {

    bd2::MapElement::Type::Empty,     // 0
    bd2::MapElement::Type::Wall,      // 1
    bd2::MapElement::Type::Exit,      // 2
    bd2::MapElement::Type::Ground,    // 3
    bd2::MapElement::Type::Diamond,   // 5
    bd2::MapElement::Type::Player,    // 8
    bd2::MapElement::Type::Butterfly, // 6
    bd2::MapElement::Type::Firefly,   // 7
    bd2::MapElement::Type::Boulder,   // 4
};

bd2::MapElement::MapElement(Type _type, MapCoordinates _position)
    : type_(_type), position_(_position) {}

void bd2::MapElement::loadTextures(
    const ResourceHandler<sf::Texture> &textures_handler, int tile_size) {

    // load a static texture depending on the type of the map element
    switch (type_) {
    case Type::Wall:
        static_texture_ = textures_handler[resources::Textures::WALL];
        break;

    case Type::Exit:
        static_texture_ = textures_handler[resources::Textures::EXIT];
        break;

    case Type::Ground:
        static_texture_ = textures_handler[resources::Textures::GROUND];
        break;

    default:
        break;
    }

    // set a static texture
    setTexture(*static_texture_);

    /* scale the texture to get proper dimensions of a tile */
    float texture_x = static_cast<float>(static_texture_->getSize().x);
    float texture_y = static_cast<float>(static_texture_->getSize().y);

    float scale_x = static_cast<float>(tile_size) / texture_x;
    float scale_y = static_cast<float>(tile_size) / texture_y;

    setScale(sf::Vector2f(scale_x, scale_y));
}

bd2::MapCoordinates bd2::MapElement::getMapPosition() const { return position_; }

bool bd2::MapElement::isMoveable() const { return false; }