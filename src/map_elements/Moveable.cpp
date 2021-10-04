#include "boulder-dash2/map_elements/Moveable.hpp"

bd2::Moveable::Moveable(Type _type, const MapCoordinates &_position,
                        sf::Time _move_duration)
    : MapElement(_type, _position), move_duration_(_move_duration), new_move_(false),
      move_time_(sf::seconds(0)), is_moving_(false), is_move_ended_(false) {}

sf::Vector2f bd2::Moveable::getMoveOffset() const {

    if (is_moving_)
        return move_offset_;
    else
        return sf::Vector2f(0, 0);
}

bd2::MapCoordinates bd2::Moveable::getPlannedMove() const { return planned_move_; }

void bd2::Moveable::startMove() {

    is_moving_ = true;
    new_move_ = true;

    if (move_time_ > move_duration_) {
        move_time_ -= move_duration_;
    } else {
        move_time_ = sf::milliseconds(0);
    }

    /** If the new move is the same as the previous one, make small initial
     * offset (proportional to the time left from the previous move) to make
     * the movement animation look more fluent */
    if (current_move_ == planned_move_) {

        float move_step = move_time_ / move_duration_;
        move_offset_.x += move_step * static_cast<float>(current_move_.c);
        move_offset_.y += move_step * static_cast<float>(current_move_.r);
    }

    current_move_ = planned_move_;
    planned_move_ = {0, 0};
}

bd2::Moveable::State bd2::Moveable::getMoveState() const {

    if (is_moving_)
        return State::IS_MOVING;

    if (is_move_ended_)
        return State::ENDED_MOVE;

    if (planned_move_)
        return State::PLANNED_MOVE;

    return State::NO_MOVE;
}

void bd2::Moveable::finishMove() {

    is_move_ended_ = false;
    map_position_ += current_move_;

    move_offset_ = {0, 0};
}

void bd2::Moveable::revertMove() {

    new_move_ = true;
    move_time_ = move_duration_ - move_time_;

    map_position_ += current_move_;
    move_offset_.x -= static_cast<float>(current_move_.c);
    move_offset_.y -= static_cast<float>(current_move_.r);

    current_move_ = -current_move_;
}

void bd2::Moveable::simulateMovement(sf::Time elapsed_time) {

    if (is_moving_) {

        move_time_ += elapsed_time;

        /* stop the movement if it's finished */
        if (move_time_ > move_duration_) {

            is_moving_ = false;
            is_move_ended_ = true;
        }

        /* make a step proportional to the elapsed time */
        float move_step = elapsed_time / move_duration_;
        move_offset_.x += move_step * static_cast<float>(current_move_.c);
        move_offset_.y += move_step * static_cast<float>(current_move_.r);
    }
}