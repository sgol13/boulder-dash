#include "boulder-dash2/map_elements/Player.hpp"

bd2::Player::Player(Type _type, MapCoordinates _position)
    : MapElement(_type, _position), Moveable(_type, _position, PLAYER_MOVE_DURATION) {
}

void bd2::Player::simulate(sf::Time elapsed_time) {

    // simulate moduls
    simulateMovement(elapsed_time);

    // interpret arrow keys
    if (getMoveState() == State::NO_MOVE) {

        if (abs(arrow_keys_.r) + abs(arrow_keys_.c) == 1) {
            planned_move_ = arrow_keys_;
        }

    } else {

        if (move_time_ < 0.1f * move_duration_) {
            move_beginning_arrow_keys_ = arrow_keys_;
        }

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
}

void bd2::Player::loadTextures(const ResourceHandler<sf::Texture> &textures_handler,
                               unsigned int tile_size) {

    static_texture_ = textures_handler[resources::Textures::BOULDER];

    // set a static texture
    setTexture(*static_texture_);

    // scale the texture to get proper dimensions of a tile */
    float texture_x = static_cast<float>(static_texture_->getSize().x);
    float texture_y = static_cast<float>(static_texture_->getSize().y);

    float scale_x = static_cast<float>(tile_size) / texture_x;
    float scale_y = static_cast<float>(tile_size) / texture_y;

    setScale(sf::Vector2f(scale_x, scale_y));
}

void bd2::Player::passArrowKeysPosition(MapCoordinates arrow_keys) {
    arrow_keys_ = arrow_keys;
}