#include "boulder-dash2/map_elements/MapElement.hpp"

bool bd2::MapElement::Compare::operator()(const std::weak_ptr<MapElement> &el1,
                                          const std::weak_ptr<MapElement> &el2) {

    auto p1 = el1.lock();
    auto p2 = el2.lock();

    // if one of the pointers is expired
    if (p1 && !p2)
        return true;

    if (!p1 && p2)
        return false;

    if (!p1 && !p2)
        return false;

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

    Type::Empty,     // 0
    Type::Wall,      // 1
    Type::Exit,      // 2
    Type::Ground,    // 3
    Type::Diamond,   // 5
    Type::Player,    // 8
    Type::Butterfly, // 6
    Type::Firefly,   // 7
    Type::Boulder,   // 4
    Type::Explosion, // 9
};

bd2::MapElement::MapElement(Type _type, const MapCoordinates &_map_position)
    : type_(_type), map_position_(_map_position), is_animating_(false),
      is_looped_(false) {

    float x = static_cast<float>(map_position_.c * TILE_SIZE);
    float y = static_cast<float>(map_position_.r * TILE_SIZE);

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
        startAnimation(*basic_texture_, DIAMOND_ANIMATION_DURATION);
        break;

    case MapElement::Type::Boulder:
        basic_texture_ = textures_handler[resources::Textures::BOULDER];
        startAnimation(*basic_texture_);
        break;

    case MapElement::Type::Explosion:
        basic_texture_ = textures_handler[resources::Textures::EXPLOSION];
        startAnimation(*basic_texture_, EXPLOSION_DURATION, sf::seconds(0), false);
        break;

    default:
        break;
    }
}

bd2::MapCoordinates bd2::MapElement::getMapPosition() const { return map_position_; }

void bd2::MapElement::startAnimation(const sf::Texture &texture, sf::Time duration,
                                     sf::Time initial_time, bool looped) {

    is_animating_ = true;
    is_looped_ = looped;

    animation_duration_ = duration;
    animation_time_ = initial_time;

    setTexture(texture);

    float texture_height = static_cast<float>(texture.getSize().y);
    float scale = static_cast<float>(TILE_SIZE) / texture_height;
    setScale(scale, scale);
}

void bd2::MapElement::simulateAnimation(sf::Time elapsed_time) {

    if (is_animating_ && animation_duration_ > sf::seconds(0)) {

        animation_time_ += elapsed_time;

        if (animation_time_ > animation_duration_ && !is_looped_) {
            is_animating_ = false;
            return;
        }

        animation_time_ %= animation_duration_;

        auto texture_size = getTexture()->getSize();
        int frames_number = texture_size.x / texture_size.y;

        float animation_progress = animation_time_ / animation_duration_;
        int current_frame = static_cast<int>(static_cast<float>(frames_number) *
                                             (animation_progress));

        sf::IntRect frame_rectangle;
        frame_rectangle.left = current_frame * texture_size.y;
        frame_rectangle.top = 0;
        frame_rectangle.width = texture_size.y;
        frame_rectangle.height = texture_size.y;

        setTextureRect(frame_rectangle);
    }
}

bool bd2::MapElement::isAnimating() const { return is_animating_; }

std::vector<bd2::MapCoordinates> bd2::MapElement::getAllMapPositions() const {

    std::vector<MapCoordinates> all_map_positions;
    all_map_positions.push_back(map_position_);
    return all_map_positions;
}