#include "boulder-dash2/map_elements/Player.hpp"

bd2::Player::Player(Type _type, const MapCoordinates &_map_position)
    : Moveable(_type, _map_position, PLAYER_MOVE_DURATION),
      planned_move_(MapCoordinates(0, 0)), previous_move_left_(true) {}

bd2::MapCoordinates bd2::Player::getPlannedMove(const Map3x3 &map3x3) {

    (void)map3x3;
    return planned_move_;
}

void bd2::Player::startMove(const MapCoordinates &new_move) {

    Moveable::startMove(new_move);
    startMoveAnimation();
    planned_move_ = {0, 0};
}

void bd2::Player::finishMove() {

    Moveable::finishMove();
    if (!planned_move_) {
        startAnimation(*basic_texture_, PLAYER_STANDING_ANIMATION_DURATION);
    }
}

void bd2::Player::reverseMove() {

    Moveable::reverseMove();
    planned_move_ = {0, 0};
    startMoveAnimation();
}

void bd2::Player::loadTextures(const ResourceHandler<sf::Texture> &textures_handler) {

    basic_texture_ = textures_handler[resources::Textures::PLAYER_STANDING];
    move_left_texture_ = textures_handler[resources::Textures::PLAYER_MOVING_LEFT];
    move_right_texture_ = textures_handler[resources::Textures::PLAYER_MOVING_RIGHT];

    startAnimation(*basic_texture_, PLAYER_STANDING_ANIMATION_DURATION);
}

void bd2::Player::setPlannedMove(const MapCoordinates &new_planned_move) {
    planned_move_ = new_planned_move;
}

void bd2::Player::startMoveAnimation() {

    if (getCurrentMove() == DIR_LEFT) {
        startAnimation(*move_left_texture_, PLAYER_MOVE_DURATION);
        previous_move_left_ = true;

    } else if (getCurrentMove() == DIR_RIGHT) {
        startAnimation(*move_right_texture_, PLAYER_MOVE_DURATION);
        previous_move_left_ = false;

    } else if (previous_move_left_) {
        startAnimation(*move_left_texture_, PLAYER_MOVE_DURATION);

    } else {
        startAnimation(*move_right_texture_, PLAYER_MOVE_DURATION);
    }
}