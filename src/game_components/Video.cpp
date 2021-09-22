#include "boulder-dash2/game_components/Video.hpp"

bd2::Video::Video(sf::RenderWindow &_window,
                  const ResourceHandler<sf::Texture> &_textures_handler)
    : Engine(_window), textures_handler_(_textures_handler) {}

void bd2::Video::processVideo() {

    window_.clear(sf::Color::Black);

    window_.display();
}