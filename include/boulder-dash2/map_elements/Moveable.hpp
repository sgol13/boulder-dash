#ifndef BD2_MOVEABLE_HPP
#define BD2_MOVEABLE_HPP

#include "boulder-dash2/defs.hpp"
#include "boulder-dash2/map_elements/MapElement.hpp"

namespace bd2 {

class Moveable : virtual public MapElement {
  public:
    // ==========================================================================
    // MOVE STATES
    // ==========================================================================
    enum class State {
        NO_MOVE,      // is not going to do any move
        PLANNED_MOVE, // planned to do a move and it should be initialised
        IS_MOVING,    // is currently moving
        ENDED_MOVE    // a move is ended and the procedure should be finished
    };
    // ==========================================================================

    /** Constructor - as an argument takes the real type of the element
     * and ist initial position (row and column) */
    Moveable(Type _type, const MapCoordinates &_position, sf::Time _move_duration);

    /** Loads needed textures from the ResourceHandler given as a pararameter.
     * The second parameter describes the expected size of the sprite tile after
     * scaling.*/
    /* virtual void loadTextures(const ResourceHandler<sf::Texture> &textures_handler,
                              unsigned int tile_size) override = 0; */

    /* This function is called once a turn to let an object execute its operations */
    virtual void simulate(sf::Time elapsed_time) override = 0;

    /* Returns the vector what is the move offset relative to a tile */
    sf::Vector2f getMoveOffset() const;

    MapCoordinates getPlannedMove() const;

    State getMoveState() const;

    /* Functions initialising the move */
    void startMove();

    void finishMove();

    void revertMove();

  protected:
    void simulateMovement(sf::Time elapsed_time);

    /* Duration of a move for this type of object */
    const sf::Time move_duration_;

    /* Direction in which the object is moving */
    MapCoordinates current_move_;

    MapCoordinates planned_move_;

    bool new_move_;

    /* The time that passed from the beginning of the move */
    sf::Time move_time_;

  private:
    /* Flag indicating if the object is currently moving */
    bool is_moving_;

    bool is_move_ended_;

    /* Current move offset relative to the tile (in fractions of tile size)  */
    sf::Vector2f move_offset_;
};

} // namespace bd2

#endif
