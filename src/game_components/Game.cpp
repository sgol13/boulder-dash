#include "boulder-dash2/game_components/Game.hpp"

bd2::Game::Game(sf::RenderWindow &_window,
                const ResourceHandler<sf::Texture> &_textures_handler,
                const ResourceHandler<sf::Font> &_fonts_handler)
    : Engine(_window), Video(_window, _textures_handler, _fonts_handler),
      Input(_window) {}

int bd2::Game::play(const std::shared_ptr<const Level> level) {

    initialiseEngine(level);
    initialiseVideo();

    // game loop
    while (!exit_) {

        processInputOperations();
        processVideoOperations();
        processEngineOperations();
    }

    return 0;
}