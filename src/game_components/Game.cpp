#include "boulder-dash2/game_components/Game.hpp"

bd2::Game::Game(sf::RenderWindow &_window,
                const ResourceHandler<sf::Texture> &_textures_handler)
    : Video(_window, _textures_handler), Input(_window), Engine(_window) {}

int bd2::Game::play(const Level &level) {

    while (window_.isOpen()) {
    }
}