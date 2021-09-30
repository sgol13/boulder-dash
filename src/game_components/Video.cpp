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

    // initialise map elements which were created during the current turn
    for (auto &weak_object : new_objects_) {

        if (auto object = weak_object.lock()) {

            object->loadTextures(textures_handler_, tile_size_);
            object->setPosition(tilePosition(object->getMapPosition()));
        }
    }

    for (auto &weak_object : simulated_objects_) {

        if (auto object = std::dynamic_pointer_cast<Moveable>(weak_object.lock())) {

            auto relative_move_offset = object->getMoveOffset();
            auto absolute_move_offset =
                relative_move_offset * static_cast<float>(tile_size_);
            auto no_offset_position = tilePosition(object->getMapPosition());

            auto move_offset_position = absolute_move_offset + no_offset_position;

            object->setPosition(move_offset_position);
        }
    }

    // DRAWING
    window_.clear(sf::Color::Black);

    // draw all map elements
    for (auto &object : simulated_objects_) {

        window_.draw(*object.lock());

        // std::cout << object.lock()->getMapPosition() << "\n";
    }

    window_.display();
}

sf::Vector2f bd2::Video::tilePosition(MapCoordinates position) {

    float x = static_cast<float>(position.c * tile_size_);
    float y = static_cast<float>(upper_bar_size_ + position.r * tile_size_);

    return sf::Vector2f(x, y);
}