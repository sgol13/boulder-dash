#ifndef BD2_INPUT_HPP
#define BD2_INPUT_HPP

#include "boulder-dash2/defs.hpp"
#include "boulder-dash2/game_components/Engine.hpp"

namespace bd2 {

class Input : virtual public Engine {
  public:
    /* Constructor*/
    Input(sf::RenderWindow &_window);

  protected:
    /* Processes all input things - to be called once a turn */
    void processInputOperations();

  private:
    /* Processes window events */
    void handleEvents();

    /* Processes KeyPressed event */
    void handleKeyPressed(const sf::Event::KeyEvent &key);

    /* Processes game control - arrows */
    void handleControl();
};

} // namespace bd2

#endif