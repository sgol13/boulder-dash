#include "boulder-dash2/game_components/Menu.hpp"


bd2::Menu::Menu(sf::RenderWindow &_window,
                const ResourceHandler<sf::Texture> &_textures_handler,
                const ResourceHandler<sf::Font> &_fonts_handler,
                const ResourceHandler<sf::SoundBuffer> &_sounds_handler,
                const int _levels_num)
    : window_(_window),
      textures_handler_(_textures_handler),
      fonts_handler_(_fonts_handler),
      sounds_handler_(_sounds_handler),
      levels_num_(_levels_num),
      exit_menu_(false),
      current_menu_option_(1),
      player_(MapElement::Type::Player, MapCoordinates(0, 0)) {

    menu_size_.x = MENU_WIDTH;
    menu_size_.y = MENU_ABOVE_GAME_NAME_GAP_HEIGHT + MENU_GAME_NAME_FONT_SIZE;
    menu_size_.y += MENU_BELOW_GAME_NAME_GAP_HEIGHT;
    menu_size_.y += MENU_BELOW_OPTIONS_TEXTS_GAP_HEIGHT;
    menu_size_.y += (levels_num_ + 1) *
                    (MENU_OPTIONS_TEXTS_SIZE + MENU_BETWEEN_OPTIONS_TEXT_GAP_HEIGHT);

    player_.loadTextures(textures_handler_);


    sf::Vector2f text_position;
    game_name_text_.setString("BOULDER DASH 2");
    game_name_text_.setFont(*fonts_handler_[resources::Fonts::PIXEL_FONT]);
    game_name_text_.setFillColor(GREY_COLOR);
    game_name_text_.setCharacterSize(MENU_GAME_NAME_FONT_SIZE);
    text_position.x = MENU_WIDTH / 2 - game_name_text_.getLocalBounds().width / 2;
    text_position.y = MENU_ABOVE_GAME_NAME_GAP_HEIGHT;
    game_name_text_.setPosition(text_position);

    text_position.x = MENU_OPTIONS_TEXTS_POSITION_X;
    text_position.y += MENU_GAME_NAME_FONT_SIZE + MENU_BELOW_GAME_NAME_GAP_HEIGHT;

    options_texts_.resize(levels_num_ + 1);
    options_texts_.front().setString("EXIT");
    for (unsigned int i = 1; i < options_texts_.size(); i++) {
        options_texts_[i].setString("LEVEL " + std::to_string(i));
    }

    for (unsigned int i = 0; i < options_texts_.size(); i++) {
        options_texts_[i].setFont(*fonts_handler_[resources::Fonts::PIXEL_FONT]);
        options_texts_[i].setCharacterSize(MENU_OPTIONS_TEXTS_SIZE);
        options_texts_[i].setFillColor(GREY_COLOR);
        options_texts_[i].setPosition(text_position);

        text_position.y += MENU_OPTIONS_TEXTS_SIZE;
        text_position.y += MENU_BETWEEN_OPTIONS_TEXT_GAP_HEIGHT;
    }

    change_option_sound_.setBuffer(*sounds_handler_[resources::Sounds::MENU_SOUND]);
    change_option_sound_.setVolume(50.f);
}

int bd2::Menu::open() {

    exit_menu_ = false;

    while (window_.isOpen() && !exit_menu_) {

        handleEvents();

        auto elapsed_time = clock_.restart();
        player_.simulateAnimation(elapsed_time);
        setPlayerPosition();
        float scale = static_cast<float>(MENU_PLAYER_SIZE) /
                      static_cast<float>(player_.getTexture()->getSize().y);
        player_.setScale(sf::Vector2f(scale, scale));

        window_.clear(sf::Color::Black);
        window_.setView(getMenuView());

        window_.draw(game_name_text_);
        window_.draw(player_);
        for (auto &text : options_texts_) {
            window_.draw(text);
        }

        window_.display();
    }

    if (!window_.isOpen())
        return 0;

    return current_menu_option_;
}

void bd2::Menu::handleEvents() {

    sf::Event event;
    while (window_.pollEvent(event)) {

        switch (event.type) {
        case sf::Event::Closed: // exit the game
            exit_menu_ = true;
            window_.close();
            break;

        case sf::Event::KeyPressed:

            if (window_.hasFocus()) {
                handleKeyPressed(event.key);
            }
            break;

        default:
            break;
        }
    }
}

void bd2::Menu::handleKeyPressed(const sf::Event::KeyEvent &key) {

    switch (key.code) {
    case sf::Keyboard::C:
        exit_menu_ = true;
        window_.close();
        break;

    case sf::Keyboard::Return: // exit the game - enter
        exit_menu_ = true;
        break;

    case sf::Keyboard::Up:

        if (--current_menu_option_ < 0) {
            current_menu_option_ = 0;

        } else {
            change_option_sound_.play();
        }
        break;

    case sf::Keyboard::Down:

        if (++current_menu_option_ > levels_num_) {
            current_menu_option_--;

        } else {
            change_option_sound_.play();
        }
        break;

    default:
        break;
    }
}

void bd2::Menu::setPlayerPosition() {

    sf::Vector2f position;
    position.x = MENU_OPTIONS_TEXTS_POSITION_X -
                 MENU_BETWEEN_OPTIONS_TEXT_GAP_HEIGHT - MENU_PLAYER_SIZE;
    position.y = MENU_ABOVE_GAME_NAME_GAP_HEIGHT + MENU_GAME_NAME_FONT_SIZE;
    position.y += MENU_BELOW_GAME_NAME_GAP_HEIGHT;
    position.y += static_cast<float>(
        current_menu_option_ *
        (MENU_OPTIONS_TEXTS_SIZE + MENU_BETWEEN_OPTIONS_TEXT_GAP_HEIGHT));

    player_.setPosition(position);
}


sf::View bd2::Menu::getMenuView() {

    sf::FloatRect view_area;
    view_area.left = 0;
    view_area.top = 0;
    view_area.width = static_cast<float>(menu_size_.x);
    view_area.height = static_cast<float>(menu_size_.y);

    sf::View view;
    view.reset(view_area);

    sf::FloatRect viewport;
    auto window_size = window_.getSize();

    if (window_size.y * menu_size_.x < window_size.x * menu_size_.y) {

        viewport.top = 0.f;
        viewport.height = 1.f;
        float margin =
            (static_cast<float>(window_size.x) -
             static_cast<float>(menu_size_.x) * static_cast<float>(window_size.y) /
                 static_cast<float>(menu_size_.y)) /
            static_cast<float>(2 * window_size.x);
        viewport.left = margin;
        viewport.width = 1.f - 2.f * margin;

    } else {

        viewport.left = 0.f;
        viewport.width = 1.f;
        float margin =
            (static_cast<float>(window_size.y) -
             static_cast<float>(menu_size_.y) * static_cast<float>(window_size.x) /
                 static_cast<float>(menu_size_.x)) /
            static_cast<float>(2 * window_size.y);
        viewport.top = margin;
        viewport.height = 1.f - 2.f * margin;
    }

    view.setViewport(viewport);
    return view;
}