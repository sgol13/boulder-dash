#include "boulder-dash2/map_elements/Moveable.hpp"

bd2::Moveable::Moveable(Type _type, MapCoordinates _position, sf::Time _move_duration)
    : MapElement(_type, _position), move_duration_(_move_duration), is_moving_(false),
      is_move_ended_(false) {}

sf::Vector2f bd2::Moveable::getMoveOffset() const {
    if (is_moving_)
        return move_offset_;
    else
        return sf::Vector2f(0, 0);
}

bd2::MapCoordinates bd2::Moveable::getPlannedMove() const {

    if (is_moving_)
        return {0, 0};
    else
        return move_direction_;
}

void bd2::Moveable::startMove() {

    is_moving_ = true;
    move_time_ = sf::milliseconds(0);

    move_offset_ = {0, 0};
}

bd2::Moveable::State bd2::Moveable::getMoveState() const {

    if (is_moving_)
        return State::IS_MOVING;

    if (is_move_ended_)
        return State::ENDED_MOVE;

    if (move_direction_)
        return State::PLANNED_MOVE;

    return State::NO_MOVE;
}

void bd2::Moveable::finishMove() {
    is_move_ended_ = false;
    position_ += move_direction_;

    move_direction_ = {0, 0};
}

void bd2::Moveable::simulateMovement(sf::Time elapsed_time) {

    if (is_moving_) {

        move_time_ += elapsed_time;

        /* stop the movement if it's finished */
        if (move_time_ > move_duration_) {
            is_moving_ = false;
            is_move_ended_ = true;
            return;
        }

        /* make a step proportional to the elapsed time */
        float move_step = elapsed_time / move_duration_;
        move_offset_.x += move_step * static_cast<float>(move_direction_.c);
        move_offset_.y += move_step * static_cast<float>(move_direction_.r);
    }
}