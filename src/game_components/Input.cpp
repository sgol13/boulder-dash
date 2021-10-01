#include "boulder-dash2/game_components/Input.hpp"

bd2::Input::Input(sf::RenderWindow &_window) : Engine(_window) {}

void bd2::Input::processInputOperations() {

    handleEvents();
    handleControl();
}

void bd2::Input::handleEvents() {

    sf::Event event;
    while (window_.pollEvent(event)) {

        switch (event.type) {

        case sf::Event::Closed: // exit the game
            exit_ = true;
            window_.close();
            break;

        case sf::Event::KeyPressed:
            handleKeyPressed(event.key);
            break;

        default:
            break;
        }
    }
}

void bd2::Input::handleKeyPressed(const sf::Event::KeyEvent &key) {

    switch (key.code) {
    case sf::Keyboard::C: // exit the game
        exit_ = true;
        break;

    default:
        break;
    }
}

void bd2::Input::handleControl() {

    if (window_.hasFocus()) {

        MapCoordinates arrow_keys = {0, 0};

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            arrow_keys += DIR_UP;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            arrow_keys += DIR_RIGHT;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            arrow_keys += DIR_DOWN;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            arrow_keys += DIR_LEFT;
        }

        player_->passArrowKeysPosition(arrow_keys);
    }
}