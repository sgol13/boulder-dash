#include "boulder-dash2/game_components/Game.hpp"

bd2::Game::Game(sf::RenderWindow &_window,
                const ResourceHandler<sf::Texture> &_textures_handler)
    : Video(_window, _textures_handler), Input(_window),
      Engine(_window, _textures_handler) {}

int bd2::Game::play(const std::shared_ptr<const Level> level) {

    initialiseLevel(level);

    // game loop
    while (!exit_) {

        processInputOperations();
        processEngineOperations();
        processVideoOperations();
    }
}