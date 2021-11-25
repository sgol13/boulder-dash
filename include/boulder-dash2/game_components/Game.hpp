#ifndef BD2_GAME_HPP
#define BD2_GAME_HPP

#include "boulder-dash2/ResourceHandler.hpp"
#include "boulder-dash2/defs.hpp"
#include "boulder-dash2/game_components/Audio.hpp"
#include "boulder-dash2/game_components/Input.hpp"
#include "boulder-dash2/game_components/Video.hpp"

namespace bd {

class Game : private Video, private Audio, private Input {
  public:
    /* Constructor */
    Game(sf::RenderWindow &_window,
         const ResourceHandler<sf::Texture> &_textures_handler,
         const ResourceHandler<sf::Font> &_fonts_handler,
         const ResourceHandler<sf::SoundBuffer> &_sounds_handler);

    /* Main game function. Returns the score or -1 if the game was stopped. */
    int play(const std::shared_ptr<const Level> level);

  private:
};

} // namespace bd

#endif