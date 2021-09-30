#include "boulder-dash2/map_elements/Player.hpp"

bd2::Player::Player(Type _type, MapCoordinates _position)
    : MapElement(_type, _position), Moveable(_type, _position, PLAYER_MOVE_DURATION) {
}

void bd2::Player::simulate(sf::Time elapsed_time) {

    simulateMovement(elapsed_time);

    if (getMoveState() != State::IS_MOVING) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            move_direction_ = DIR_UP;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            move_direction_ = DIR_RIGHT;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            move_direction_ = DIR_DOWN;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            move_direction_ = DIR_LEFT;
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