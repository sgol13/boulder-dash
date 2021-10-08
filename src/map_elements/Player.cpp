#include "boulder-dash2/map_elements/Player.hpp"

bd2::Player::Player(Type _type, const MapCoordinates &_map_position)
    : Moveable(_type, _map_position), planned_move_(MapCoordinates(0, 0)),
      previous_move_left_(true), dead_(false),
      temporary_move_duration_(sf::seconds(0)) {}

bd2::MapCoordinates bd2::Player::getPlannedMove(const Map3x3 &map3x3) {

    (void)map3x3;
    return planned_move_;
}

void bd2::Player::startMove(const MapCoordinates &new_move,
                            sf::Time new_move_duration) {

    if (new_move_duration == sf::seconds(0)) {
        new_move_duration = PLAYER_MOVE_DURATION;
    }

    if (temporary_move_duration_ != sf::seconds(0)) {
        new_move_duration = temporary_move_duration_;
        temporary_move_duration_ = sf::seconds(0);
    }

    Moveable::startMove(new_move, new_move_duration);
    startMoveAnimation();
    planned_move_ = {0, 0};
}

void bd2::Player::finishMove() {

    Moveable::finishMove();
    startAnimation(*basic_texture_, PLAYER_STANDING_ANIMATION_DURATION);
}

void bd2::Player::reverseMove() {

    move_duration_ = PLAYER_MOVE_DURATION;

    Moveable::reverseMove();
    planned_move_ = {0, 0};
    startMoveAnimation();
}

void bd2::Player::loadTextures(const ResourceHandler<sf::Texture> &textures_handler) {

    basic_texture_ = textures_handler[resources::Textures::PLAYER_STANDING];
    move_left_texture_ = textures_handler[resources::Textures::PLAYER_MOVING_LEFT];
    move_right_texture_ = textures_handler[resources::Textures::PLAYER_MOVING_RIGHT];
    death_texture_ = textures_handler[resources::Textures::PLAYER_DEATH];
    start_texture_ = textures_handler[resources::Textures::PLAYER_START];

    startAnimation(*start_texture_, PLAYER_START_ANIMATION_DURATION, sf::seconds(0),
                   false);
}

void bd2::Player::setPlannedMove(const MapCoordinates &new_planned_move) {
    planned_move_ = new_planned_move;
}

void bd2::Player::setTempMoveDuration(sf::Time new_temporary_move_duration) {
    temporary_move_duration_ = new_temporary_move_duration;
}

void bd2::Player::startMoveAnimation() {

    if (getCurrentMove() == DIR_LEFT) {
        startAnimation(*move_left_texture_, PLAYER_MOVE_DURATION, sf::seconds(0),
                       false);
        previous_move_left_ = true;

    } else if (getCurrentMove() == DIR_RIGHT) {
        startAnimation(*move_right_texture_, PLAYER_MOVE_DURATION, sf::seconds(0),
                       false);
        previous_move_left_ = false;

    } else if (previous_move_left_) {
        startAnimation(*move_left_texture_, PLAYER_MOVE_DURATION, sf::seconds(0),
                       false);

    } else {
        startAnimation(*move_right_texture_, PLAYER_MOVE_DURATION, sf::seconds(0),
                       false);
    }
}

void bd2::Player::die() {

    startAnimation(*death_texture_, PLAYER_DEATH_ANIMATION_DURATION, sf::seconds(0),
                   false);
    dead_ = true;
}

void bd2::Player::simulateAnimation(sf::Time elapsed_time) {

    if (isAnimating() == false) {
        startAnimation(*basic_texture_, PLAYER_STANDING_ANIMATION_DURATION,
                       sf::seconds(0), true);
    }

    MapElement::simulateAnimation(elapsed_time);
}

void bd2::Player::startAnimation(const sf::Texture &texture, sf::Time duration,
                                 sf::Time initial_time, bool looped) {

    if (!dead_) {
        MapElement::startAnimation(texture, duration, initial_time, looped);
    }
}