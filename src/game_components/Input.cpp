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

void bd2::Input::handleControl() {}