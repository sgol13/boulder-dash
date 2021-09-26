#ifndef BD2_ENGINE_HPP
#define BD2_ENGINE_HPP

#include "boulder-dash2/Level.hpp"
#include "boulder-dash2/defs.hpp"
#include "boulder-dash2/map_elements/MapElement.hpp"

namespace bd2 {

class Engine {
  public:
    /* Constructor */
    Engine(sf::RenderWindow &_window);

  protected:
    /* Processes all game engine operations - to be called once a turn*/
    void processEngineOperations();

    /* Creates an initial state of the map on the basis of level object */
    void initialiseLevel(const std::shared_ptr<const Level> level);

    // reference for a window
    sf::RenderWindow &window_;

    // flag indicating if the game is going to be exited
    bool exit_;

    /** The list of newly created map elements. It cointains only the elements
     * which were created in a current turn so that other components
     * (Video, Input, Audio) could perform some operations on new elements
     * e.g. initialise them. */
    std::vector<std::shared_ptr<MapElement>> new_map_elements_;

  private:
    /* Creates a new map element of given type on [pos_i, pos_j] position */
    void addMapElement(MapElement::Type type, int pos_i, int pos_j);

    // map
    std::vector<std::vector<std::shared_ptr<MapElement>>> map_;
    int rows_num_;
    int columns_num_;
};

} // namespace bd2

#endif