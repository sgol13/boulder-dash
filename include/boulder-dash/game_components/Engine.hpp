// Szymon Golebiowski
// Boulder Dash

#ifndef BD_ENGINE_HPP
#define BD_ENGINE_HPP

#include "boulder-dash/Level.hpp"
#include "boulder-dash/MapCoordinates.hpp"
#include "boulder-dash/defs.hpp"
#include "boulder-dash/map_elements/Boulder.hpp"
#include "boulder-dash/map_elements/Exit.hpp"
#include "boulder-dash/map_elements/Flyable.hpp"
#include "boulder-dash/map_elements/MapElement.hpp"
#include "boulder-dash/map_elements/Moveable.hpp"
#include "boulder-dash/map_elements/Player.hpp"

namespace bd {

class Engine {
  private:
    // ==========================================================================
    /** DOUBLE TILE - this class allows storing two objects on the same map tile.
     * Is is necessary because there can be two objects on the opposide sides
     * of the tile. */
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
    Engine(sf::RenderWindow &_window);

  protected:
    /* Initialises engine at the beginning of every game */
    void initialiseEngine(const std::shared_ptr<const Level> level);

    /* Processes all game engine operations - to be called once a turn*/
    void processEngineOperations();

    /* Finalises engine operations at the end of every game */
    void finaliseEngine();

    // reference for a window
    sf::RenderWindow &window_;

    bool end_game_;
    bool exit_game_;
    bool win_game_;
    bool pause_game_;

    /** The list of newly created map elements. It cointains only the elements
     * which were created in a current turn so that other components
     * (Video, Input, Audio) could perform some operations on new elements
     * e.g. initialise them. */
    std::vector<std::weak_ptr<MapElement>> new_objects_;

    /** The list of sounds that should be initiated by Audio module. The list
     * is cleared every turn */
    std::vector<resources::Sounds> sounds_to_play_;

    // all objects on the map
    std::vector<std::weak_ptr<MapElement>> map_objects_;

    sf::Time turn_elapsed_time_;
    sf::Time total_elapsed_time_;
    sf::Time time_limit_;

    std::shared_ptr<Player> player_;
    std::shared_ptr<Exit> exit_;

    MapCoordinates map_size_;

    int picked_diamonds_;
    int required_diamonds_;
    int score_;

  private:
    void addMapElement(MapElement::Type type, const MapCoordinates &position);

    /** Returns the sub-map containing information about objects
     * surrounding the center object.*/
    Moveable::Map3x3 getMap3x3(const MapCoordinates &center);

    void startObjectMove(const std::shared_ptr<Moveable> &object,
                         const MapCoordinates &planned_move);

    void finishObjectMove(const std::shared_ptr<Moveable> &object);

    void killObject(const std::shared_ptr<MapElement> &object,
                    const std::shared_ptr<MapElement> &killer = nullptr);


    bool checkCollision(const std::shared_ptr<Moveable> &moveable_object,
                        const MapCoordinates &move);

    bool collideObjects(const std::shared_ptr<Moveable> &moveable_object,
                        const std::shared_ptr<MapElement> &target_object);

    void collideObjectsInMove(std::shared_ptr<MapElement> object_1,
                              std::shared_ptr<MapElement> object_2);

    bool collidePlayer(const std::shared_ptr<Player> &player,
                       const std::shared_ptr<MapElement> &target_object);

    /* Orders a particular sound from Audio module */
    void playSound(resources::Sounds sound);

    /* Finished the game - when the player entered the exit or was killed */
    void gameOver();

    /** Function template which removes from a vector all elements that satisfy
     * the predicate. */
    template <class T>
    void eraseFromVectorIf(std::vector<T> &vector,
                           std::function<bool(const T &)> predicate);

    sf::Clock time_score_transfer_clock_;

    // all moveable objects on the map
    std::vector<std::weak_ptr<Moveable>> moveable_objects_;

    // score from left seconds
    int time_score_;

    /** List of tiles which are partly covered by two objects. Tiles are
     * removed from the list when there is only one object on them. Tiles on this
     * list are checked every turn to see if the objects collided */
    std::vector<std::vector<DoubleTile>::iterator> double_tiles_;

    /** List of objects that wered killed during the current turn
     * and should be removed */
    std::set<std::shared_ptr<MapElement>, MapElement::Compare> killed_objects_;

    std::vector<MapCoordinates> diamonds_to_add_;

    std::vector<std::shared_ptr<MapElement>> explosions_;

    std::vector<std::vector<DoubleTile>> map_;

    sf::Clock clock_;
};


template <class T>
void bd::Engine::eraseFromVectorIf(std::vector<T> &vector,
                                   std::function<bool(const T &)> predicate) {

    auto new_end = std::remove_if(vector.begin(), vector.end(), predicate);
    vector.erase(new_end, vector.end());
}

} // namespace bd

#endif