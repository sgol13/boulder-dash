// Szymon Golebiowski
// Boulder Dash

#ifndef BD_VIDEO_HPP
#define BD_VIDEO_HPP

#include "boulder-dash/ResourceHandler.hpp"
#include "boulder-dash/defs.hpp"
#include "boulder-dash/game_components/Engine.hpp"
#include "boulder-dash/map_elements/MapElement.hpp"

namespace bd {

class Video : virtual public Engine {
  public:
    Video(sf::RenderWindow &_window,
          const ResourceHandler<sf::Texture> &_textures_handler,
          const ResourceHandler<sf::Font> &_fonts_handler);

  protected:
    void initialiseVideo();

    /* Processes all video operations - to be called once a turn */
    void processVideoOperations();

  private:
    /* Moves view area so that it covers only map area */
    void fitViewAreaToMap();

    float getViewScale();

    sf::View getMapView(float scale, sf::Vector2u window_size);

    sf::View getInterfaceView(float scale, sf::Vector2u window_size);

    void updateInterface();

    void moveInterfaceElementToColumn(sf::Transformable &element, int column);

    void setEndGameInterface();

    void setPauseInterface();

    MapElement interface_diamond_;
    sf::Text diamonds_counter_text_;
    sf::Text keys_info_text_;
    sf::Text time_left_text_;
    sf::Text score_text_;
    sf::Text game_over_text_;
    sf::Text victory_score_text_;
    sf::Text end_game_info_text_;
    sf::Text pause_text_;

    const ResourceHandler<sf::Texture> &textures_handler_;
    const ResourceHandler<sf::Font> &fonts_handler_;

    sf::FloatRect map_view_area_;

    float map_width_;
    float map_height_;
};

} // namespace bd

#endif