#ifndef BD2_ENGINE_HPP
#define BD2_ENGINE_HPP

#include "boulder-dash2/Level.hpp"
#include "boulder-dash2/defs.hpp"

namespace bd2 {

class Engine {
  public:
    /* Constructor */
    Engine(sf::RenderWindow &_window);

  protected:
    sf::RenderWindow &window_;


  private:
};

} // namespace bd2

#endif