#ifndef BD2_VIDEO_HPP
#define BD2_VIDEO_HPP

#include "boulder-dash2/ResourceHandler.hpp"
#include "boulder-dash2/defs.hpp"
#include "boulder-dash2/game_components/Engine.hpp"

namespace bd2 {

class Video : virtual public Engine {
  public:
    /* Constructor */
    Video(sf::RenderWindow &_window,
          const ResourceHandler<sf::Texture> &_textures_handler);

  protected:
  private:
    const ResourceHandler<sf::Texture> &textures_handler_;
};

} // namespace bd2

#endif