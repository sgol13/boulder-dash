#include "boulder-dash2/game_components/Video.hpp"

bd2::Video::Video(sf::RenderWindow &_window,
                  const ResourceHandler<sf::Texture> &_textures_handler,
                  const ResourceHandler<sf::Font> &_fonts_handler)
    : Engine(_window), textures_handler_(_textures_handler),
      fonts_handler_(_fonts_handler) {}

void bd2::Video::initialiseVideo() {

    // set a view area with the player in the center
    auto window_size = window_.getSize();
    auto player_center = player_->getCenterPosition();

    float scale = getViewScale();

    view_area_.width = static_cast<float>(window_size.x) * scale;
    view_area_.height = static_cast<float>(window_size.y) * scale;
    view_area_.left = player_center.x - 0.5f * view_area_.width;
    view_area_.top = player_center.y - 0.5f * view_area_.height;

    fitViewAreaToMap();

    for (auto &weak_object : new_objects_) {
        if (auto object = weak_object.lock()) {

            object->loadTextures(textures_handler_);
        }
    }
}

void bd2::Video::processVideoOperations() {

    // PROCESSING OBJECTS
    // initialise map elements which were created during the current turn
    for (auto &weak_object : new_objects_) {

        if (auto object = weak_object.lock()) {

            object->loadTextures(textures_handler_);
        }
    }

    for (auto &weak_object : map_objects_) {

        if (auto object = weak_object.lock()) {

            object->simulateAnimation(turn_elapsed_time_);
        }
    }

    // SETTING VIEW
    auto window_size = window_.getSize();
    auto player_center = player_->getCenterPosition();

    float scale = getViewScale();

    // move the view area to keep the player inside (+ margins)
    view_area_.width = static_cast<float>(window_size.x) * scale;
    view_area_.height = static_cast<float>(window_size.y) * scale;

    float horizontal_margin = VIEW_MARGIN_RATIO * view_area_.width;
    float vertical_margin = VIEW_MARGIN_RATIO * view_area_.height;

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
    std::sort(map_objects_.begin(), map_objects_.end(), MapElement::Compare());

    window_.clear(sf::Color::Black);

    // draw all map elements
    for (auto &object : map_objects_) {

        window_.draw(*object.lock());
    }

    window_.display();
}

void bd2::Video::fitViewAreaToMap() {

    float map_width = static_cast<float>(TILE_SIZE * map_size_.c);
    float map_height = static_cast<float>(TILE_SIZE * map_size_.r);

    view_area_.left = std::min(view_area_.left, map_width - view_area_.width);
    view_area_.top = std::min(view_area_.top, map_height - view_area_.height);

    view_area_.left = std::max(view_area_.left, 0.0f);
    view_area_.top = std::max(view_area_.top, 0.0f);
}

float bd2::Video::getViewScale() {

    float screen_height = static_cast<float>(sf::VideoMode::getDesktopMode().height);
    float scale = (TILE_SIZE * VERTICAL_TILES_NUM) / screen_height;

    return scale;
}