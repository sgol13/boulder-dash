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

            if (window_.hasFocus()) {
                handleKeyPressed(event.key);
            }

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

    MapCoordinates arrow_keys = {0, 0};

    // read the current states of the arrow keys
    if (window_.hasFocus()) {

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
    }

    // set the player's planned move on the basis of the arrow keys' states
    if (abs(arrow_keys.r) + abs(arrow_keys.c) <= 1) {
        player_->setPlannedMove(arrow_keys);
    }

    if ((arrow_keys.r != 0 && player_->getCurrentMove().r == -arrow_keys.r) ||
        (arrow_keys.c != 0 && player_->getCurrentMove().c == -arrow_keys.c)) {

        player_->reverseMove();
    }
}