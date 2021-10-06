#ifndef BD2_VIDEO_HPP
#define BD2_VIDEO_HPP

#include "boulder-dash2/ResourceHandler.hpp"
#include "boulder-dash2/defs.hpp"
#include "boulder-dash2/game_components/Engine.hpp"
#include "boulder-dash2/map_elements/MapElement.hpp"

namespace bd2 {

class Video : virtual public Engine {
  public:
    /* Constructor */
    Video(sf::RenderWindow &_window,
          const ResourceHandler<sf::Texture> &_textures_handler,
          const ResourceHandler<sf::Font> &_fonts_handler);

  protected:
    /* Initial graphic settings */
    void initialiseVideo();

    /* Processes all video operations - to be called once a turn */
    void processVideoOperations();

  private:
    /* Moves view area so that it covers only map area */
    void fitViewAreaToMap();

    float getViewScale();

    const ResourceHandler<sf::Texture> &textures_handler_;
    const ResourceHandler<sf::Font> &fonts_handler_;

    sf::FloatRect view_area_;
};

} // namespace bd2

#endif