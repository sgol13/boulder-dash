// Szymon Golebiowski
// Boulder Dash 2, 2021

#include "boulder-dash2/game_components/Video.hpp"

bd::Video::Video(sf::RenderWindow &_window,
                 const ResourceHandler<sf::Texture> &_textures_handler,
                 const ResourceHandler<sf::Font> &_fonts_handler)
    : Engine(_window),
      interface_diamond_(MapElement::Type::Diamond, MapCoordinates(0, 0)),
      textures_handler_(_textures_handler),
      fonts_handler_(_fonts_handler) {}

void bd::Video::initialiseVideo() {

    // COLUMN 0 - diamonds counter
    interface_diamond_.loadTextures(textures_handler_);
    float texture_height =
        static_cast<float>(interface_diamond_.getTexture()->getSize().y);
    float diamond_scale = 0.7f * UPPER_BAR_SIZE / texture_height;
    interface_diamond_.setScale(diamond_scale, diamond_scale);

    diamonds_counter_text_.setFont(*fonts_handler_[resources::Fonts::PIXEL_FONT]);
    diamonds_counter_text_.setFillColor(sf::Color::White);
    diamonds_counter_text_.setCharacterSize(INTERFACE_FONT_SIZE);

    // COLUMN 1 - keys info
    keys_info_text_.setString("enter - exit\nspace - pause");
    keys_info_text_.setFont(*fonts_handler_[resources::Fonts::PIXEL_FONT]);
    keys_info_text_.setFillColor(sf::Color::White);
    keys_info_text_.setCharacterSize(INTERFACE_FONT_SIZE / 2);

    // COLUMN 2 - timer
    time_left_text_.setFont(*fonts_handler_[resources::Fonts::PIXEL_FONT]);
    time_left_text_.setFillColor(sf::Color::White);
    time_left_text_.setCharacterSize(INTERFACE_FONT_SIZE);

    // COLUMN 3 - score
    score_text_.setFont(*fonts_handler_[resources::Fonts::PIXEL_FONT]);
    score_text_.setFillColor(sf::Color::Yellow);
    score_text_.setCharacterSize(INTERFACE_FONT_SIZE);

    // GAME OVER
    game_over_text_.setFont(*fonts_handler_[resources::Fonts::PIXEL_FONT]);
    game_over_text_.setFillColor(sf::Color::Magenta);
    game_over_text_.setOutlineColor(sf::Color::White);
    game_over_text_.setCharacterSize(GAME_OVER_FONT_SIZE);
    game_over_text_.setOutlineThickness(3);

    end_game_info_text_.setString("Press enter to continue...");
    end_game_info_text_.setFont(*fonts_handler_[resources::Fonts::PIXEL_FONT]);
    end_game_info_text_.setFillColor(sf::Color::Magenta);
    end_game_info_text_.setOutlineColor(sf::Color::White);
    end_game_info_text_.setCharacterSize(VICTORY_TEXT_FONT_SIZE);
    end_game_info_text_.setOutlineThickness(2);

    victory_score_text_.setFont(*fonts_handler_[resources::Fonts::PIXEL_FONT]);
    victory_score_text_.setFillColor(sf::Color::Magenta);
    victory_score_text_.setOutlineColor(sf::Color::White);
    victory_score_text_.setCharacterSize(GAME_OVER_SCORE_FONT_SIZE);
    victory_score_text_.setOutlineThickness(2);

    // PAUSE
    pause_text_.setString("PAUSE");
    pause_text_.setFont(*fonts_handler_[resources::Fonts::PIXEL_FONT]);
    pause_text_.setFillColor(sf::Color::White);
    pause_text_.setCharacterSize(PAUSE_TEXT_FONT_SIZE);

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

void bd::Video::processVideoOperations() {

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
    window_size.x =
        std::max(window_size.x, static_cast<unsigned int>(MIN_WINDOW_WIDTH));
    window_size.y =
        std::max(window_size.y, static_cast<unsigned int>(MIN_WINDOW_HEIGHT));
    window_.setSize(window_size);

    float scale = getViewScale();

    window_.clear(sf::Color::Black);

    window_.setView(getMapView(scale, window_size));

    std::sort(map_objects_.begin(), map_objects_.end(), MapElement::Compare());

    for (auto &weak_object : map_objects_) {

        if (auto object = weak_object.lock()) {
            window_.draw(*object);
        }
    }

    if (pause_game_) {

        setPauseInterface();
        window_.draw(pause_text_);
    }

    if (end_game_) {

        setEndGameInterface();

        window_.draw(game_over_text_);
        window_.draw(end_game_info_text_);

        if (win_game_) {
            window_.draw(victory_score_text_);
        }
    }

    window_.setView(getInterfaceView(scale, window_size));

    updateInterface();

    window_.draw(interface_diamond_);
    window_.draw(diamonds_counter_text_);
    window_.draw(keys_info_text_);
    window_.draw(time_left_text_);
    window_.draw(time_left_text_);
    window_.draw(score_text_);

    window_.display();
}

void bd::Video::fitViewAreaToMap() {

    map_view_area_.left =
        std::min(map_view_area_.left, map_width_ - map_view_area_.width);
    map_view_area_.top =
        std::min(map_view_area_.top, map_height_ - map_view_area_.height);

    map_view_area_.left = std::max(map_view_area_.left, 0.0f);
    map_view_area_.top = std::max(map_view_area_.top, 0.0f);
}

float bd::Video::getViewScale() {

    float screen_height = static_cast<float>(sf::VideoMode::getDesktopMode().height);
    float scale = (TILE_SIZE * VERTICAL_TILES_NUM) / screen_height;

    return scale;
}

sf::View bd::Video::getMapView(float scale, sf::Vector2u window_size) {

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

sf::View bd::Video::getInterfaceView(float scale, sf::Vector2u window_size) {

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

void bd::Video::updateInterface() {

    // COLUMN 0 - diamonds counter
    interface_diamond_.simulateAnimation(turn_elapsed_time_);
    interface_diamond_.setPosition(0.15f * UPPER_BAR_SIZE, 0.15f * UPPER_BAR_SIZE);
    moveInterfaceElementToColumn(interface_diamond_, 0);

    std::ostringstream oss;
    oss << std::right << std::setfill(' ') << std::setw(3);
    oss << std::min(picked_diamonds_, required_diamonds_);
    oss << "/" << required_diamonds_;
    diamonds_counter_text_.setString(oss.str());
    diamonds_counter_text_.setPosition(UPPER_BAR_SIZE * 0.8f, INTERFACE_TEXT_POS);
    moveInterfaceElementToColumn(diamonds_counter_text_, 0);

    // COLUMN 1 - keys info
    keys_info_text_.setPosition(0, INTERFACE_TEXT_POS);
    moveInterfaceElementToColumn(keys_info_text_, 1);

    // COLUMN 2 - timer
    oss.str(std::string());
    if (!end_game_ || win_game_) {
        int time_left =
            static_cast<int>((time_limit_ - total_elapsed_time_).asSeconds());
        time_left = std::max(0, time_left);
        oss << std::right << std::setfill('0') << std::setw(3) << time_left;
        time_left_text_.setString(oss.str());

        if (time_left_text_.getFillColor() == sf::Color::White && time_left < 10 &&
            !end_game_) {
            time_left_text_.setFillColor(sf::Color::Red);
        }
    }

    time_left_text_.setPosition(0, INTERFACE_TEXT_POS);
    moveInterfaceElementToColumn(time_left_text_, 2);

    // COLUMN 3 - score
    oss.str(std::string());
    oss << std::right << std::setfill('0') << std::setw(4) << score_;
    score_text_.setString(oss.str());
    score_text_.setPosition(0, INTERFACE_TEXT_POS);
    moveInterfaceElementToColumn(score_text_, 3);
}

void bd::Video::moveInterfaceElementToColumn(sf::Transformable &element, int column) {

    sf::Vector2f offset;
    offset.x =
        static_cast<float>(column) * (static_cast<float>(window_.getSize().x) / 4.f);
    offset.y = map_height_;

    element.move(offset);
}

void bd::Video::setEndGameInterface() {

    if (win_game_) {
        game_over_text_.setString("VICTORY");

    } else {
        game_over_text_.setString("GAME OVER");
    }

    sf::Vector2f text_position;
    text_position.x = map_view_area_.left + map_view_area_.width / 2 -
                      game_over_text_.getLocalBounds().width / 2;
    text_position.y = map_view_area_.top + map_view_area_.height / 4;
    game_over_text_.setPosition(text_position);


    victory_score_text_.setString("SCORE: " + std::to_string(score_));
    text_position.x = map_view_area_.left + map_view_area_.width / 2 -
                      victory_score_text_.getLocalBounds().width / 2;
    text_position.y += 1.5f * GAME_OVER_FONT_SIZE;
    victory_score_text_.setPosition(text_position);

    text_position.x = map_view_area_.left + map_view_area_.width / 2 -
                      end_game_info_text_.getLocalBounds().width / 2;
    text_position.y += 2 * GAME_OVER_SCORE_FONT_SIZE;
    end_game_info_text_.setPosition(text_position);
}

void bd::Video::setPauseInterface() {

    sf::Vector2f text_position;
    text_position.x = map_view_area_.left + map_view_area_.width / 2 -
                      pause_text_.getLocalBounds().width / 2;
    text_position.y = map_view_area_.top + map_view_area_.height / 4;
    pause_text_.setPosition(text_position);
}