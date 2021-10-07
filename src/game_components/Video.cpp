#include "boulder-dash2/game_components/Video.hpp"

bd2::Video::Video(sf::RenderWindow &_window,
                  const ResourceHandler<sf::Texture> &_textures_handler,
                  const ResourceHandler<sf::Font> &_fonts_handler)
    : Engine(_window),
      interface_diamond_(MapElement::Type::Diamond, MapCoordinates(0, 0)),
      textures_handler_(_textures_handler), fonts_handler_(_fonts_handler) {}

void bd2::Video::initialiseVideo() {

    // COLUMN 0 - diamonds counter
    interface_diamond_.loadTextures(textures_handler_);

    diamonds_counter_text_.setFont(*fonts_handler_[resources::Fonts::PIXEL_FONT]);
    diamonds_counter_text_.setFillColor(sf::Color::White);
    diamonds_counter_text_.setCharacterSize(INTERFACE_FONT_SIZE);

    // COLUMN 1 - keys info
    keys_info_text_.setString("enter - exit\nspace - pause");
    keys_info_text_.setFont(*fonts_handler_[resources::Fonts::PIXEL_FONT]);
    keys_info_text_.setFillColor(sf::Color::White);

    // COLUMN 2 - timer
    time_left_text_.setFont(*fonts_handler_[resources::Fonts::PIXEL_FONT]);
    time_left_text_.setFillColor(sf::Color::White);
    time_left_text_.setCharacterSize(INTERFACE_FONT_SIZE);

    // COLUMN 3 - score
    score_text_.setFont(*fonts_handler_[resources::Fonts::PIXEL_FONT]);
    score_text_.setFillColor(sf::Color::White);
    score_text_.setCharacterSize(INTERFACE_FONT_SIZE);

    // view area initialisation
    map_width_ = static_cast<float>(TILE_SIZE * map_size_.c);
    map_height_ = static_cast<float>(TILE_SIZE * map_size_.r);

    // set a view area with the player in the center
    auto window_size = window_.getSize();
    auto player_center = player_->getCenterPosition();

    float scale = getViewScale();

    map_view_area_.width = static_cast<float>(window_size.x) * scale;
    map_view_area_.height =
        static_cast<float>(window_size.y) * scale - UPPER_BAR_SIZE;
    map_view_area_.left = player_center.x - 0.5f * map_view_area_.width;
    map_view_area_.top = player_center.y - 0.5f * map_view_area_.height;


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
    float scale = getViewScale();

    window_.clear(sf::Color::Black);

    auto map_view = getMapView(scale, window_size);
    window_.setView(map_view);


    std::sort(map_objects_.begin(), map_objects_.end(), MapElement::Compare());

    for (auto &object : map_objects_) {

        window_.draw(*object.lock());
    }

    auto interface_view = getInterfaceView(scale, window_size);
    window_.setView(interface_view);

    updateInterfaceData();

    window_.draw(rect);
    window_.draw(interface_diamond_);
    window_.draw(diamonds_counter_text_);
    window_.draw(keys_info_text_);
    window_.draw(time_left_text_);
    window_.draw(time_left_text_);
    window_.draw(score_text_);

    window_.display();
}

void bd2::Video::fitViewAreaToMap() {

    map_view_area_.left =
        std::min(map_view_area_.left, map_width_ - map_view_area_.width);
    map_view_area_.top =
        std::min(map_view_area_.top, map_height_ - map_view_area_.height);

    map_view_area_.left = std::max(map_view_area_.left, 0.0f);
    map_view_area_.top = std::max(map_view_area_.top, 0.0f);
}

float bd2::Video::getViewScale() {

    float screen_height = static_cast<float>(sf::VideoMode::getDesktopMode().height);
    float scale = (TILE_SIZE * VERTICAL_TILES_NUM) / screen_height;

    return scale;
}

sf::View bd2::Video::getMapView(float scale, sf::Vector2u window_size) {

    auto player_center = player_->getCenterPosition();

    // move the view area to keep the player inside (+ margins)
    map_view_area_.width = static_cast<float>(window_size.x) * scale;
    map_view_area_.height =
        static_cast<float>(window_size.y) * scale - UPPER_BAR_SIZE;

    float horizontal_margin = VIEW_MARGIN_RATIO * map_view_area_.width;
    float vertical_margin = VIEW_MARGIN_RATIO * map_view_area_.height;

    map_view_area_.left =
        std::min(map_view_area_.left, player_center.x - horizontal_margin);
    map_view_area_.left =
        std::max(map_view_area_.left,
                 player_center.x + horizontal_margin - map_view_area_.width);

    map_view_area_.top =
        std::min(map_view_area_.top, player_center.y - vertical_margin);
    map_view_area_.top =
        std::max(map_view_area_.top,
                 player_center.y + vertical_margin - map_view_area_.height);

    // move a view to keep it on the map
    fitViewAreaToMap();

    sf::View view;
    view.reset(map_view_area_);

    float upper_bar_window_ratio =
        UPPER_BAR_SIZE / (scale * static_cast<float>(window_size.y));

    // the viewport is the whole screen apart from the upper bar
    view.setViewport(sf::FloatRect(0.f, upper_bar_window_ratio, 1.f,
                                   1.f - upper_bar_window_ratio));

    return view;
}

sf::View bd2::Video::getInterfaceView(float scale, sf::Vector2u window_size) {

    (void)scale;

    sf::FloatRect interface_view_area;
    interface_view_area.left = 0.f;
    interface_view_area.top = map_height_;
    interface_view_area.width = static_cast<float>(window_size.x);
    interface_view_area.height = UPPER_BAR_SIZE;

    sf::View view;
    view.reset(interface_view_area);
    float upper_bar_window_ratio =
        UPPER_BAR_SIZE / (scale * static_cast<float>(window_size.y));
    view.setViewport(sf::FloatRect(0.f, 0.f, 1.f, upper_bar_window_ratio));

    return view;
}

void bd2::Video::updateInterfaceData() {


    // COLUMN 0 - diamonds counter
    interface_diamond_.simulateAnimation(turn_elapsed_time_);
    interface_diamond_.setPosition(0, 0);
    moveInterfaceElementToColumn(interface_diamond_, 0);

    std::ostringstream oss;
    oss << std::right << std::setfill(' ') << std::setw(3) << picked_diamonds_;
    oss << " / " << required_diamonds_;
    diamonds_counter_text_.setString(oss.str());
    diamonds_counter_text_.setPosition(UPPER_BAR_SIZE, INTERFACE_TEXT_POS);
    moveInterfaceElementToColumn(diamonds_counter_text_, 0);

    // COLUMN 1 - keys info
    moveInterfaceElementToColumn(keys_info_text_, 1);

    // COLUMN 2 - timer
    oss.str(std::string());
    int time_left = static_cast<int>((time_limit_ - total_elapsed_time_).asSeconds());
    oss << std::right << std::setfill('0') << std::setw(3) << time_left;
    time_left_text_.setString(oss.str());
    time_left_text_.setPosition(0, INTERFACE_TEXT_POS);
    moveInterfaceElementToColumn(time_left_text_, 2);

    // COLUMN 3 - score
    oss.str(std::string());
    int current_score = 257;
    oss << std::right << std::setfill('0') << std::setw(5) << current_score;
    score_text_.setString(oss.str());
    score_text_.setPosition(0, INTERFACE_TEXT_POS);
    moveInterfaceElementToColumn(score_text_, 3);
}

void bd2::Video::moveInterfaceElementToColumn(sf::Transformable &element,
                                              int column) {

    sf::Vector2f offset;
    offset.x =
        static_cast<float>(column) * (static_cast<float>(window_.getSize().x) / 4.f);
    offset.y = map_height_;

    element.move(offset);
}