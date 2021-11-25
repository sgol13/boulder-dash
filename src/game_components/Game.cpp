#include "boulder-dash2/game_components/Game.hpp"

bd::Game::Game(sf::RenderWindow &_window,
                const ResourceHandler<sf::Texture> &_textures_handler,
                const ResourceHandler<sf::Font> &_fonts_handler,
                const ResourceHandler<sf::SoundBuffer> &_sounds_handler)
    : Engine(_window),
      Video(_window, _textures_handler, _fonts_handler),
      Audio(_window, _sounds_handler),
      Input(_window) {

    srand(static_cast<unsigned int>(time(0)));
}

int bd::Game::play(const std::shared_ptr<const Level> level) {

    initialiseEngine(level);
    initialiseVideo();
    initialiseAudio();

    // game loop
    while (window_.isOpen() && exit_game_ == false) {

        processInputOperations();
        processEngineOperations();
        processVideoOperations();
        processAudioOperations();
    }

    finaliseEngine();
    finaliseAudio();

    if (!win_game_)
        score_ = 0;

    return score_;
}