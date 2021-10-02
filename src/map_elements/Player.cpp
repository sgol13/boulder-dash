#include "boulder-dash2/map_elements/Player.hpp"

bd2::Player::Player(Type _type, MapCoordinates _position)
    : MapElement(_type, _position), Moveable(_type, _position, PLAYER_MOVE_DURATION),
      Animatable(_type, _position), previous_left_(true) {}

void bd2::Player::simulate(sf::Time elapsed_time) {

    // interpret arrow keys
    if (getMoveState() == State::NO_MOVE) {

        if (abs(arrow_keys_.r) + abs(arrow_keys_.c) == 1) {
            planned_move_ = arrow_keys_;
        }

    } else {

        if ((current_move_.r != 0 && current_move_.r == -arrow_keys_.r) ||
            (current_move_.c != 0 && current_move_.c == -arrow_keys_.c)) {
            revertMove();

        } else if (getMoveState() == State::ENDED_MOVE && planned_move_ == false &&
                   current_move_ == arrow_keys_) {

            planned_move_ = arrow_keys_;

        } else {

            if (current_move_.r) {
                arrow_keys_.r = 0;

            } else if (current_move_.c) {
                arrow_keys_.c = 0;
            }

            MapCoordinates new_direction = {0, 0};
            int counter = 0;

            if (arrow_keys_.r == -1) {
                new_direction = DIR_UP;
                counter++;

            } else if (arrow_keys_.c == 1) {
                new_direction = DIR_RIGHT;
                counter++;

            } else if (arrow_keys_.r == 1) {
                new_direction = DIR_DOWN;
                counter++;

            } else if (arrow_keys_.c == -1) {
                new_direction = DIR_LEFT;
                counter++;
            }

            if (counter == 1) {
                planned_move_ = new_direction;
            }
        }
    }

    if (new_move_) {

        if (current_move_ == DIR_LEFT ||
            ((current_move_ == DIR_UP || current_move_ == DIR_DOWN) &&
             previous_left_)) {

            startAnimation(move_left_texture_, 2.f * move_duration_, move_time_);
            previous_left_ = true;

        } else {
            startAnimation(move_right_texture_, 2.f * move_duration_, move_time_);
            previous_left_ = false;
        }

        new_move_ = false;
    }

    if (isAnimating() == false) {

        startAnimation(standing_textures_[rand() % static_cast<unsigned int>(
                                                       standing_textures_.size())],
                       PLAYER_STANDING_ANIMATION_DURATION);
    }

    // simulate moduls
    simulateMovement(elapsed_time);
    simulateAnimation(elapsed_time);
}

void bd2::Player::loadTextures(const ResourceHandler<sf::Texture> &textures_handler,
                               unsigned int tile_size) {

    tile_size_ = tile_size;

    standing_textures_.push_back(textures_handler[resources::Textures::PLAYER_BLINK]);
    standing_textures_.push_back(textures_handler[resources::Textures::PLAYER_LEG]);
    standing_textures_.push_back(
        textures_handler[resources::Textures::PLAYER_BLINK_LEG]);

    move_left_texture_ = textures_handler[resources::Textures::PLAYER_LEFT];
    move_right_texture_ = textures_handler[resources::Textures::PLAYER_RIGHT];
}

void bd2::Player::passArrowKeysPosition(MapCoordinates arrow_keys) {
    arrow_keys_ = arrow_keys;
}