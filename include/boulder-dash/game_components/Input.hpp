// Szymon Golebiowski
// Boulder Dash

#ifndef BD_INPUT_HPP
#define BD_INPUT_HPP

#include "boulder-dash/defs.hpp"
#include "boulder-dash/game_components/Engine.hpp"

namespace bd {

class Input : virtual public Engine {
  public:
    Input(sf::RenderWindow &_window);

  protected:
    /* Processes all input things - to be called once a turn */
    void processInputOperations();

  private:
    void handleEvents();

    void handleKeyPressed(const sf::Event::KeyEvent &key);

    /* Processes game control - arrow keys */
    void handleControl();
};

} // namespace bd

#endif