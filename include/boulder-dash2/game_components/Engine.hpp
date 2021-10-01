#ifndef BD2_ENGINE_HPP
#define BD2_ENGINE_HPP

#include "boulder-dash2/Level.hpp"
#include "boulder-dash2/MapCoordinates.hpp"
#include "boulder-dash2/defs.hpp"
#include "boulder-dash2/map_elements/MapElement.hpp"
#include "boulder-dash2/map_elements/Player.hpp"

namespace bd2 {

class Engine {
  private:
    // ==========================================================================
    // DOUBLE TILE
    // ==========================================================================
    class DoubleTile {
      public:
        DoubleTile();

        DoubleTile(const std::shared_ptr<MapElement> &_ptr0);

        DoubleTile(const std::shared_ptr<MapElement> &_ptr0,
                   const std::shared_ptr<MapElement> &_ptr1);

        std::shared_ptr<MapElement> &
        operator=(const std::shared_ptr<MapElement> &ptr);

        std::shared_ptr<MapElement> &operator[](int n);

        int size() const;

        void remove(int n);

        void remove(const std::shared_ptr<MapElement> &ptr_remove);

        bool add(const std::shared_ptr<MapElement> &ptr_add);

        operator std::shared_ptr<MapElement> &();

      private:
        std::shared_ptr<MapElement> ptr0_;
        std::shared_ptr<MapElement> ptr1_;

        const static std::shared_ptr<MapElement> empty_ptr; // = nullptr
    };
    // ==========================================================================

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

    /* Main game clock - measures time elapsed between turns */
    sf::Clock clock_;

    // pointer to the player object
    std::shared_ptr<Player> player_;

    std::set<std::weak_ptr<MapElement>, MapElement::Compare> simulated_objects_;

    // sizes of the current level: {number of rows, number of columns}
    MapCoordinates map_size_;

  private:
    /* Creates a new map element of given type on [row, column] position */
    void addMapElement(MapElement::Type type, MapCoordinates position);

    void startObjectMove(const std::shared_ptr<Moveable> &object);

    void finishObjectMove(const std::shared_ptr<Moveable> &object);

    // map
    std::vector<std::vector<DoubleTile>> map_;
};

} // namespace bd2

#endif