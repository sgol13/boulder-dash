#include "boulder-dash2/game_components/Video.hpp"

bd2::Video::Video(sf::RenderWindow &_window,
                  const ResourceHandler<sf::Texture> &_textures_handler)
    : Engine(_window, _textures_handler) {}

void bd2::Video::processVideoOperations() {

    window_.clear(sf::Color::Black);

    /* Remove all non-existing drawable objects.
        They are alwas in the beginning of the set */
    while (!drawable_objects_.empty() && drawable_objects_.begin()->expired())
        drawable_objects_.erase(drawable_objects_.begin());



    window_.display();
}