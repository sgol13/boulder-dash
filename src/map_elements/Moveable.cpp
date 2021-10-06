#include "boulder-dash2/map_elements/Moveable.hpp"

bd2::Moveable::Moveable(Type _type, const MapCoordinates &_map_position)
    : MapElement(_type, _map_position), move_duration_(sf::seconds(0)),
      move_time_(sf::seconds(0)), move_phase_(MovePhase::STANDING) {}

void bd2::Moveable::startMove(const MapCoordinates &new_move,
                              sf::Time new_move_duration) {

    move_phase_ = MovePhase::STARTED_MOVE;

    // special case for temporary changing the move duration
    // move_time_ should be set to 0 to keep an animation fluent
    if (move_duration_ != new_move_duration) {
        move_time_ = sf::seconds(0);
    }
    move_duration_ = new_move_duration;
    move_time_ %= move_duration_;
    current_move_ = new_move;
}

bd2::Moveable::MovePhase bd2::Moveable::getMovePhase() const { return move_phase_; }

bd2::MapCoordinates bd2::Moveable::getCurrentMove() const { return current_move_; }

void bd2::Moveable::finishMove() {

    move_phase_ = MovePhase::STANDING;
    map_position_ += current_move_;

    float x = static_cast<float>(map_position_.c * TILE_SIZE);
    float y = static_cast<float>(map_position_.r * TILE_SIZE);
    setPosition(x, y);
}

void bd2::Moveable::reverseMove() {

    move_time_ = move_duration_ - move_time_;
    map_position_ += current_move_;
    current_move_ = -current_move_;
}

void bd2::Moveable::simulateMovement(sf::Time elapsed_time) {

    if (move_phase_ == MovePhase::STARTED_MOVE) {
        move_phase_ = MovePhase::MOVING;
    }

    if (move_phase_ == MovePhase::MOVING) {

        move_time_ += elapsed_time;

        if (move_time_ > move_duration_) {
            move_phase_ = MovePhase::ENDED_MOVE;
        }

        float x = static_cast<float>(map_position_.c * TILE_SIZE);
        float y = static_cast<float>(map_position_.r * TILE_SIZE);

        float move_progress = move_time_ / move_duration_;
        x += move_progress * static_cast<float>(current_move_.c * TILE_SIZE);
        y += move_progress * static_cast<float>(current_move_.r * TILE_SIZE);

        setPosition(x, y);
    }
}

std::vector<bd2::MapCoordinates> bd2::Moveable::getAllMapPositions() const {

    auto all_map_positions = MapElement::getAllMapPositions();

    if (getMovePhase() != MovePhase::STANDING) {

        auto target_position = map_position_ + current_move_;
        all_map_positions.push_back(target_position);
    }
    return all_map_positions;
}

sf::Vector2f bd2::Moveable::getCenterPosition() const {

    sf::Vector2f position = getPosition();
    position.x += TILE_SIZE / 2;
    position.y += TILE_SIZE / 2;

    return position;
}