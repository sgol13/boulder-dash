#ifndef BD2_ENGINE_HPP
#define BD2_ENGINE_HPP

#include "boulder-dash2/Level.hpp"
#include "boulder-dash2/MapCoordinates.hpp"
#include "boulder-dash2/defs.hpp"
#include "boulder-dash2/map_elements/MapElement.hpp"
#include "boulder-dash2/map_elements/Player.hpp"

namespace bd2 {

class Engine {
  public:
    /* Constructor */
    Engine(sf::RenderWindow &_window);

  protected:
    /* Creates an initial state of the map on the basis of level object */
    void initialiseEngine(const std::shared_ptr<const Level> level);

    /* Processes all game engine operations - to be called once a turn*/
    void processEngineOperations();

    // reference for a window
    sf::RenderWindow &window_;

    // flag indicating if the game is going to be exited
    bool exit_;

    /** The list of newly created map elements. It cointains only the elements
     * which were created in a current turn so that other components
     * (Video, Input, Audio) could perform some operations on new elements
     * e.g. initialise them. */
    std::vector<std::weak_ptr<MapElement>> new_objects_;

    /* Main game clock - measures common time in game */
    sf::Clock clock_;

  private:
    /* Creates a new map element of given type on [row, column] position */
    void addMapElement(MapElement::Type type, MapCoordinates position);

    // map
    std::vector<std::vector<std::shared_ptr<MapElement>>> map_;

    // sizes of the current level: {number of rows, number of columns}
    MapCoordinates map_size_;

    // pointer to the player object
    std::shared_ptr<Player> player_;
};

} // namespace bd2

#endif