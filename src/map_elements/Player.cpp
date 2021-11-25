// Szymon Golebiowski
// Boulder Dash

#include "boulder-dash/map_elements/Player.hpp"

bd::Player::Player(Type _type, const MapCoordinates &_map_position)
    : Moveable(_type, _map_position),
      planned_move_(MapCoordinates(0, 0)),
      previous_move_left_(true),
      dead_(false),
      temporary_move_duration_(sf::seconds(0)) {}

void bd::Player::loadTextures(const ResourceHandler<sf::Texture> &textures_handler) {

    basic_texture_ = textures_handler[resources::Textures::PLAYER_STANDING];
    move_left_texture_ = textures_handler[resources::Textures::PLAYER_MOVING_LEFT];
    move_right_texture_ = textures_handler[resources::Textures::PLAYER_MOVING_RIGHT];
    death_texture_ = textures_handler[resources::Textures::PLAYER_DEATH];
    start_texture_ = textures_handler[resources::Textures::PLAYER_BORNING];

    startAnimation(*start_texture_, PLAYER_BORNING_ANIMATION_DURATION, sf::seconds(0),
                   false);
}

void bd::Player::startMove(const MapCoordinates &new_move,
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

void bd::Player::finishMove() {

    Moveable::finishMove();
    startAnimation(*basic_texture_, PLAYER_STANDING_ANIMATION_DURATION);
}

void bd::Player::reverseMove() {

    move_duration_ = PLAYER_MOVE_DURATION;

    Moveable::reverseMove();
    planned_move_ = {0, 0};
    startMoveAnimation();
}

void bd::Player::simulateAnimation(sf::Time elapsed_time) {

    if (isAnimating() == false) {
        startAnimation(*basic_texture_, PLAYER_STANDING_ANIMATION_DURATION);
    }

    MapElement::simulateAnimation(elapsed_time);
}

bd::MapCoordinates bd::Player::getPlannedMove(const Map3x3 &map3x3) {

    (void)map3x3;
    return planned_move_;
}

void bd::Player::setPlannedMove(const MapCoordinates &new_planned_move) {
    planned_move_ = new_planned_move;
}

void bd::Player::setTempMoveDuration(sf::Time new_temporary_move_duration) {
    temporary_move_duration_ = new_temporary_move_duration;
}

void bd::Player::die() {

    startAnimation(*death_texture_, PLAYER_DEATH_ANIMATION_DURATION, sf::seconds(0),
                   false);
    dead_ = true;
}

void bd::Player::startAnimation(const sf::Texture &texture, sf::Time duration,
                                sf::Time initial_time, bool looped) {

    if (!dead_) {
        MapElement::startAnimation(texture, duration, initial_time, looped);
    }
}

void bd::Player::startMoveAnimation() {

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