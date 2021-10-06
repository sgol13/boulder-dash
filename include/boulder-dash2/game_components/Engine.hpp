#ifndef BD2_ENGINE_HPP
#define BD2_ENGINE_HPP

#include "boulder-dash2/Level.hpp"
#include "boulder-dash2/MapCoordinates.hpp"
#include "boulder-dash2/defs.hpp"
#include "boulder-dash2/map_elements/Boulder.hpp"
#include "boulder-dash2/map_elements/Exit.hpp"
#include "boulder-dash2/map_elements/Flyable.hpp"
#include "boulder-dash2/map_elements/MapElement.hpp"
#include "boulder-dash2/map_elements/Moveable.hpp"
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

        void remove(const MapElement &object_remove);

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
    bool end_game_;

    /** The list of newly created map elements. It cointains only the elements
     * which were created in a current turn so that other components
     * (Video, Input, Audio) could perform some operations on new elements
     * e.g. initialise them. */
    std::vector<std::weak_ptr<MapElement>> new_objects_;

    sf::Time turn_elapsed_time_;

    // pointer to the player object
    std::shared_ptr<Player> player_;
    std::shared_ptr<Exit> exit_;

    std::vector<std::weak_ptr<MapElement>> map_objects_;

    // sizes of the current level: {number of rows, number of columns}
    MapCoordinates map_size_;

    int score_;

    int time_limit_;
    int required_diamonds_;

  private:
    std::vector<std::weak_ptr<Moveable>> moveable_objects_;

    /* Creates a new map element of given type on [row, column] position */
    void addMapElement(MapElement::Type type, const MapCoordinates &position);

    Moveable::Map3x3 getMap3x3(const MapCoordinates &center);

    void startObjectMove(const std::shared_ptr<Moveable> &object,
                         const MapCoordinates &planned_move);

    void finishObjectMove(const std::shared_ptr<Moveable> &object);

    void killObject(MapElement &object);

    void gameOver();

    bool checkCollision(Moveable &moveable_object, const MapCoordinates &move);

    bool collideObjects(Moveable &moveable_object, MapElement &target_object);

    bool collidePlayer(Player &player, MapElement &target_object);

    void collideObjectsInMove(std::shared_ptr<MapElement> object_1,
                              std::shared_ptr<MapElement> object_2);

    /*     template <class T>
        void removeExpiredTail(std::vector<T> &vector, std::function<void(T)>); */

    std::vector<std::vector<DoubleTile>::iterator> double_tiles_;

    std::vector<std::vector<DoubleTile>> map_;

    sf::Clock clock_;
};

} // namespace bd2

/* template <class T>
void bd2::Engine::removeExpiredTail(std::vector<T> &vector, std::function<void(T)>) {}
 */
#endif