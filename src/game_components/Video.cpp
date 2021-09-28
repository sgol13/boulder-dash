#include "boulder-dash2/game_components/Video.hpp"

bd2::Video::Video(sf::RenderWindow &_window,
                  const ResourceHandler<sf::Texture> &_textures_handler,
                  const ResourceHandler<sf::Font> &_fonts_handler)
    : Engine(_window), textures_handler_(_textures_handler),
      fonts_handler_(_fonts_handler) {}

void bd2::Video::initialiseVideo() {

    tile_size_ = sf::VideoMode::getDesktopMode().height / VERTICAL_TILES_NUM;
    upper_bar_size_ = tile_size_;
}

void bd2::Video::processVideoOperations() {

    window_.clear(sf::Color::Black);

    // initialise map elements which were created during the current turn
    for (auto &object : new_objects_) {

        object->loadTextures(textures_handler_, tile_size_);
        object->setPosition(tilePosition(object->getRow(), object->getColumn()));
        drawable_objects_.insert(object);
    }

    // draw all map elements
    for (auto &object : drawable_objects_) {

        window_.draw(*object);
    }


    /* Remove all non-existing drawable objects.
        They are alwas in the beginning of the set */
    /* while (!drawable_objects_.empty() && drawable_objects_.begin()->expired())
        drawable_objects_.erase(drawable_objects_.begin());
 */


    window_.display();
}

sf::Vector2f bd2::Video::tilePosition(int row, int column) {

    float x = static_cast<float>(column * tile_size_);
    float y = static_cast<float>(upper_bar_size_ + row * tile_size_);

    return sf::Vector2f(x, y);
}