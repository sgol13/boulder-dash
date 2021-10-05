#include "boulder-dash2/map_elements/Flyable.hpp"

bd2::Flyable::Flyable(Type _type, const MapCoordinates &_map_position)
    : Moveable(_type, _map_position) {}

void bd2::Flyable::loadTextures(
    const ResourceHandler<sf::Texture> &textures_handler) {

    switch (type_) {
    case Type::Butterfly:

        basic_texture_ = textures_handler[resources::Textures::BUTTERFLY];
        break;

    case Type::Firefly:

        basic_texture_ = textures_handler[resources::Textures::FIREFLY];
        break;

    default:
        break;
    }

    startAnimation(*basic_texture_, FLYABLE_ANIMATION_DURATION);
}

void bd2::Flyable::startMove(const MapCoordinates &new_move,
                             sf::Time new_move_duration) {

    if (new_move_duration == sf::seconds(0)) {
        new_move_duration = FLYABLE_MOVE_DURATION;
    }
    Moveable::startMove(new_move, new_move_duration);
}

bd2::MapCoordinates bd2::Flyable::getPlannedMove(const Map3x3 &map3x3) {

    MapCoordinates chosen_map_dir(0, 0);

    std::vector<MapCoordinates> possible_directions;
    for (auto &dir : DIR_AROUND4) {

        auto map_dir = dir + MapCoordinates(1, 1);

        if (map3x3[map_dir.r][map_dir.c] == Type::Empty) {
            possible_directions.push_back(map_dir);

        } else if (map3x3[map_dir.r][map_dir.c] == Type::Player) {
            chosen_map_dir = map_dir;
            break;
        }
    }

    if (!chosen_map_dir) {

        MapCoordinates current_map_dir = getCurrentMove() + MapCoordinates(1, 1);

        if (map3x3[current_map_dir.r][current_map_dir.c] == Type::Empty) {
            possible_directions.resize(possible_directions.size() + 9,
                                       current_map_dir);
        }
        int random_range = static_cast<int>(possible_directions.size());

        if (random_range > 0) {
            int random_number = rand() % random_range;
            chosen_map_dir = possible_directions[random_number];
        }
    }

    MapCoordinates planned_move = chosen_map_dir - MapCoordinates(1, 1);
    return planned_move;
}