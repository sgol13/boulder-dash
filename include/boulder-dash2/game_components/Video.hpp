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
          const ResourceHandler<sf::Texture> &_textures_handler,
          const ResourceHandler<sf::Font> &_fonts_handler);

  protected:
    /* Initial graphic settings */
    void initialiseVideo();

    /* Processes all video operations - to be called once a turn */
    void processVideoOperations();

  private:
    /** Calculate tile's position (in pixels) on the screen on the basis
     * of its position on the map (row and column) */
    sf::Vector2f tilePosition(int row, int column);

    const ResourceHandler<sf::Texture> &textures_handler_;
    const ResourceHandler<sf::Font> &fonts_handler_;

    // square tile size in pixels (depenting on the screen resolution)
    int tile_size_;

    // size of the upper interface bar (score and time) in pixels
    int upper_bar_size_;

    std::set<std::shared_ptr<MapElement>> drawable_objects_;
};

} // namespace bd2

#endif