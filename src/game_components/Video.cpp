#include "boulder-dash2/game_components/Video.hpp"

bd2::Video::Video(sf::RenderWindow &_window,
                  const ResourceHandler<sf::Texture> &_textures_handler,
                  const ResourceHandler<sf::Font> &_fonts_handler)
    : Engine(_window), textures_handler_(_textures_handler),
      fonts_handler_(_fonts_handler) {}

void bd2::Video::processVideoOperations() {

    window_.clear(sf::Color::Black);

    for (auto &element : new_map_elements_) {

        element->loadTextures(textures_handler_);
    }


    /* Remove all non-existing drawable objects.
        They are alwas in the beginning of the set */
    /* while (!drawable_objects_.empty() && drawable_objects_.begin()->expired())
        drawable_objects_.erase(drawable_objects_.begin());
 */


    window_.display();
}