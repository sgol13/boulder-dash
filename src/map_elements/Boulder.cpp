// Szymon Golebiowski
// Boulder Dash 2, 2021

#include "boulder-dash2/map_elements/Boulder.hpp"

bd::Boulder::Boulder(Type _type, const MapCoordinates &_map_position)
    : Moveable(_type, _map_position),
      left_fall_time_(sf::seconds(0)),
      center_fall_time_(sf::seconds(0)),
      right_fall_time_(sf::seconds(0)),
      is_falling_(false),
      pushed_direction_(0, 0) {}

void bd::Boulder::startMove(const MapCoordinates &new_move,
                            sf::Time new_move_duration) {

    if (new_move_duration == sf::seconds(0)) {
        new_move_duration = BOULDER_MOVE_DURATION;
    }
    Moveable::startMove(new_move, new_move_duration);
}

void bd::Boulder::pushSide(const MapCoordinates &direction) {
    pushed_direction_ = direction;
}

bd::MapCoordinates bd::Boulder::getPlannedMove(const Map3x3 &map3x3) {

    bool left_free = false;
    bool center_free = false;
    bool right_free = false;

    MapCoordinates planned_move;

    if (pushed_direction_) {
        planned_move = pushed_direction_;
        pushed_direction_ = {0, 0};
        return planned_move;
    }

    if (map3x3[1][0] == Type::Empty && map3x3[2][0] == Type::Empty) {
        left_free = true;
    }

    if (map3x3[2][1] == Type::Empty) {
        center_free = true;
    }

    if (is_falling_ &&
        (map3x3[2][1] == Type::Player || map3x3[2][1] == Type::Butterfly ||
         map3x3[2][1] == Type::Firefly)) {

        center_free = true;
    }

    if (map3x3[1][2] == Type::Empty && map3x3[2][2] == Type::Empty) {
        right_free = true;
    }

    if (center_free) {
        planned_move = DIR_DOWN;

    } else {

        if (left_free && right_free) {

            int random_number = rand() % 2;
            planned_move = random_number == 0 ? DIR_LEFT : DIR_RIGHT;

        } else if (left_free) {
            planned_move = DIR_LEFT;

        } else if (right_free) {
            planned_move = DIR_RIGHT;
        }
    }

    is_falling_ = planned_move.r;

    return planned_move;
}