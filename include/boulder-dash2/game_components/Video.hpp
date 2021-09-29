#ifndef BD2_VIDEO_HPP
#define BD2_VIDEO_HPP

#include "boulder-dash2/ResourceHandler.hpp"
#include "boulder-dash2/defs.hpp"
#include "boulder-dash2/game_components/Engine.hpp"
#include "boulder-dash2/map_elements/MapElement.hpp"
#include "boulder-dash2/map_elements/Moveable.hpp"

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
    /** Calculate tile's position (in pixels) on the screen on the basis
     * of its position on the map {row, column} */
    sf::Vector2f tilePosition(MapCoordinates position);

    const ResourceHandler<sf::Texture> &textures_handler_;
    const ResourceHandler<sf::Font> &fonts_handler_;

    // square tile size in pixels (depending on the screen resolution)
    unsigned int tile_size_;

    // size of the upper interface bar (score and time) in pixels
    unsigned int upper_bar_size_;

    std::set<std::weak_ptr<MapElement>, MapElement::Compare> drawable_objects_;
    std::set<std::weak_ptr<Moveable>, MapElement::Compare> moveable_objects_;
};

} // namespace bd2

#endif