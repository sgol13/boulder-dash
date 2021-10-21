// Szymon Golebiowski
// Boulder Dash 2, 2021

#ifndef BD2_INPUT_HPP
#define BD2_INPUT_HPP

#include "boulder-dash2/defs.hpp"
#include "boulder-dash2/game_components/Engine.hpp"

namespace bd2 {

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

} // namespace bd2

#endif