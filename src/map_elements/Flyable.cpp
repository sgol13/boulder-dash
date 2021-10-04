#include "boulder-dash2/map_elements/Flyable.hpp"

bd2::Flyable::Flyable(Type _type, MapCoordinates _position)
    : Moveable(_type, _position, FLYABLE_MOVE_DURATION) {}

void bd2::Flyable::loadTextures(
    const ResourceHandler<sf::Texture> &textures_handler) {

    switch (type_) {
    case MapElement::Type::Butterfly:

        basic_texture_ = textures_handler[resources::Textures::BUTTERFLY];
        break;

    case MapElement::Type::Firefly:

        basic_texture_ = textures_handler[resources::Textures::FIREFLY];
        break;

    default:
        break;
    }

    startAnimation(*basic_texture_, FLYABLE_ANIMATION_DURATION);
}

bd2::MapCoordinates bd2::Flyable::getPlannedMove(const Map3x3 &map3x3) const {

    MapCoordinates chosen_map_dir(0, 0);

    std::vector<MapCoordinates> possible_directions;
    for (auto &dir : DIR_AROUND4) {

        auto map_dir = dir + MapCoordinates(1, 1);

        if (map3x3[map_dir.r][map_dir.c] == MapElement::Type::Empty) {
            possible_directions.push_back(map_dir);

        } else if (map3x3[map_dir.r][map_dir.c] == MapElement::Type::Player) {
            chosen_map_dir = map_dir;
            break;
        }
    }

    if (!chosen_map_dir) {

        MapCoordinates current_map_dir = getCurrentMove() + MapCoordinates(1, 1);

        if (map3x3[current_map_dir.r][current_map_dir.c] == MapElement::Type::Empty) {
            possible_directions.resize(possible_directions.size() + 9,
                                       current_map_dir);
        }
        int random_range = static_cast<int>(possible_directions.size());

        if (random_range > 0) {
            int random_number = rand() % random_range;
            chosen_map_dir = possible_directions[random_number];
        }
    }

    MapCoordinates chosen_move = chosen_map_dir - MapCoordinates(1, 1);
    return chosen_move;
}