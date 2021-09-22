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
  private:
};

} // namespace bd2

#endif