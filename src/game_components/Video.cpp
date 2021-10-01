#include "boulder-dash2/game_components/Video.hpp"

bd2::Video::Video(sf::RenderWindow &_window,
                  const ResourceHandler<sf::Texture> &_textures_handler,
                  const ResourceHandler<sf::Font> &_fonts_handler)
    : Engine(_window), textures_handler_(_textures_handler),
      fonts_handler_(_fonts_handler) {}

void bd2::Video::initialiseVideo() {

    // dimensions
    tile_size_ = sf::VideoMode::getDesktopMode().height / VERTICAL_TILES_NUM;
    upper_bar_size_ = tile_size_;

    // set a view area with the player in the center
    auto window_size = window_.getSize();
    auto player_center =
        tileCenter(player_->getMapPosition(), player_->getMoveOffset());

    view_area_.left = player_center.x - 0.5f * static_cast<float>(window_size.x);
    view_area_.top = player_center.y - 0.5f * static_cast<float>(window_size.y);
    view_area_.width = static_cast<float>(window_size.x);
    view_area_.height = static_cast<float>(window_size.y);

    fitViewAreaToMap();
}

void bd2::Video::processVideoOperations() {

    // PROCESSING OBJECTS
    // initialise map elements which were created during the current turn
    for (auto &weak_object : new_objects_) {

        if (auto object = weak_object.lock()) {

            object->loadTextures(textures_handler_, tile_size_);
            object->setPosition(tilePosition(object->getMapPosition()));
        }
    }

    // set positions of moveable objects
    for (auto &weak_object : simulated_objects_) {

        if (auto object = std::dynamic_pointer_cast<Moveable>(weak_object.lock())) {

            auto move_offset = object->getMoveOffset();
            auto tile_position = tilePosition(object->getMapPosition(), move_offset);

            object->setPosition(tile_position);
        }
    }

    // SETTING VIEW
    auto window_size = window_.getSize();

    auto player_center =
        tileCenter(player_->getMapPosition(), player_->getMoveOffset());

    // move the view area to keep the player inside (+ margins)
    view_area_.width = static_cast<float>(window_size.x);
    view_area_.height = static_cast<float>(window_size.y);

    float horizontal_margin = VIEW_MARGIN_RATIO * static_cast<float>(window_size.x);
    float vertical_margin = VIEW_MARGIN_RATIO * static_cast<float>(window_size.y);

    view_area_.left = std::min(view_area_.left, player_center.x - horizontal_margin);
    view_area_.left = std::max(view_area_.left, player_center.x + horizontal_margin -
                                                    view_area_.width);

    view_area_.top = std::min(view_area_.top, player_center.y - vertical_margin);
    view_area_.top = std::max(view_area_.top,
                              player_center.y + vertical_margin - view_area_.height);


    // move a view to keep it on the map
    fitViewAreaToMap();

    // the viewport is the whole screen apart from the upper bar
    sf::View view;
    view.reset(view_area_);

    view.setViewport(sf::FloatRect(0.0f, 0.0f, 1.0f, 1.0f));
    window_.setView(view);

    // DRAWING
    window_.clear(sf::Color::Black);

    // draw all map elements
    for (auto &object : simulated_objects_) {

        window_.draw(*object.lock());
    }

    window_.display();
}

sf::Vector2f bd2::Video::tilePosition(const MapCoordinates &position,
                                      const sf::Vector2f &move_offset) const {

    sf::Vector2f tile_position;
    tile_position.x = static_cast<float>(position.c * tile_size_);
    tile_position.y = static_cast<float>(position.r * tile_size_);

    tile_position += move_offset * static_cast<float>(tile_size_);

    return tile_position;
}

sf::Vector2f bd2::Video::tileCenter(const MapCoordinates &position,
                                    const sf::Vector2f &move_offset) const {

    auto tile_position = tilePosition(position, move_offset);
    auto centre_offset = 0.5f * sf::Vector2f(static_cast<float>(tile_size_),
                                             static_cast<float>(tile_size_));

    return tile_position + centre_offset;
}

void bd2::Video::fitViewAreaToMap() {

    view_area_.left = std::max(view_area_.left, 0.0f);
    view_area_.top = std::max(view_area_.top, 0.0f);

    float map_width = static_cast<float>(tile_size_ * map_size_.c);
    float map_height = static_cast<float>(tile_size_ * map_size_.r);

    view_area_.left = std::min(view_area_.left, map_width - view_area_.width);
    view_area_.top = std::min(view_area_.top, map_height - view_area_.height);
}