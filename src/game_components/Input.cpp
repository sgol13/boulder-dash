// Szymon Golebiowski
// Boulder Dash 2, 2021

#include "boulder-dash2/game_components/Input.hpp"

bd2::Input::Input(sf::RenderWindow &_window) : Engine(_window) {}

void bd2::Input::processInputOperations() {

    handleEvents();

    if (!pause_game_) {
        handleControl();
    }
}

void bd2::Input::handleEvents() {

    sf::Event event;
    while (window_.pollEvent(event)) {

        switch (event.type) {

        case sf::Event::Closed: // exit the game
            end_game_ = true;
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
    case sf::Keyboard::C: // exit the game using C
        exit_game_ = true;
        window_.close();
        break;

    case sf::Keyboard::Return: // exit the game - enter
        exit_game_ = true;
        break;

    case sf::Keyboard::Space: // pause the game - space
        if (!end_game_) {
            pause_game_ = !pause_game_;
        }
        break;

    default:
        break;
    }
}

void bd2::Input::handleControl() {

    MapCoordinates arrow_keys = {0, 0};

    // read the current states of the arrow keys
    if (window_.hasFocus() && !end_game_) {

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

    if (player_->getMovePhase() == Moveable::MovePhase::MOVING) {

        if ((arrow_keys.r != 0 && player_->getCurrentMove().r == -arrow_keys.r) ||
            (arrow_keys.c != 0 && player_->getCurrentMove().c == -arrow_keys.c)) {

            player_->reverseMove();
        }
    }
}