#include "boulder-dash2/map_elements/MapElement.hpp"

bool bd2::MapElement::Compare::operator()(const std::weak_ptr<MapElement> &el1,
                                          const std::weak_ptr<MapElement> &el2) {

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

    if (it1 < it2)
        return true;

    if (it1 > it2)
        return false;

    auto coord1 = p1->getMapPosition();
    auto coord2 = p2->getMapPosition();

    if (coord1 < coord2)
        return true;

    if (coord1 > coord2)
        return false;

    // compare raw pointers
    return p1.get() < p2.get();
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

bd2::MapElement::MapElement(Type _type, const MapCoordinates &_position)
    : type_(_type), map_position_(_position) {

    float x = static_cast<float>(_position.c * TILE_SIZE);
    float y = static_cast<float>(_position.r * TILE_SIZE);

    setPosition(x, y);
}

void bd2::MapElement::loadTextures(
    const ResourceHandler<sf::Texture> &textures_handler) {

    switch (type_) {
    case MapElement::Type::Wall:
        basic_texture_ = textures_handler[resources::Textures::WALL];
        startAnimation(*basic_texture_);
        break;

    case MapElement::Type::Ground:
        basic_texture_ = textures_handler[resources::Textures::GROUND];
        startAnimation(*basic_texture_);
        break;

    case MapElement::Type::Diamond:
        basic_texture_ = textures_handler[resources::Textures::DIAMOND];
        startAnimation(*basic_texture_, DIAMOND_ANIMATION_TIME);
        break;

        /*case MapElement::Type::Explosion:
            basic_texture_ = textures_handler[resources::Textures::EXPLOSION];
            break;
        } */

    default:
        break;
    }
}

bd2::MapCoordinates bd2::MapElement::getMapPosition() const { return map_position_; }

void bd2::MapElement::startAnimation(const sf::Texture &texture, sf::Time duration,
                                     sf::Time initial_time) {

    animation_duration_ = duration;
    animation_time_ = initial_time;

    setTexture(texture);

    float texture_height = static_cast<float>(texture.getSize().y);
    float scale = static_cast<float>(TILE_SIZE) / texture_height;
    setScale(scale, scale);
}

void bd2::MapElement::simulateAnimation(sf::Time elapsed_time) {

    if (animation_duration_ > sf::seconds(0)) {

        animation_time_ += elapsed_time;
        animation_time_ %= animation_duration_;

        auto texture_size = getTexture()->getSize();
        int frames_number = texture_size.x / texture_size.y;

        int current_frame = static_cast<int>(static_cast<float>(frames_number) *
                                             (animation_time_ / animation_duration_));

        sf::IntRect frame_rectangle(current_frame * texture_size.y, 0, texture_size.y,
                                    texture_size.y);

        setTextureRect(frame_rectangle);
    }
}
