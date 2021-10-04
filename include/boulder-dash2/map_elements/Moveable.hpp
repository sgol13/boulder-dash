#ifndef BD2_MOVEABLE_HPP
#define BD2_MOVEABLE_HPP

#include "boulder-dash2/defs.hpp"
#include "boulder-dash2/map_elements/MapElement.hpp"

namespace bd2 {

class Moveable : public MapElement {
  public:
    // ==========================================================================
    // MOVE STATES
    // ==========================================================================
    enum class MovePhase {
        STANDING, // is not going to do any move
        STARTED_MOVE,
        MOVING,    // is currently moving
        ENDED_MOVE // a move is ended and the procedure should be finished
    };
    // ==========================================================================

    /** Constructor - as an argument takes the real type of the element
     * and ist initial position (row and column) */
    Moveable(Type _type, const MapCoordinates &_position, sf::Time _move_duration);

    /** Loads needed textures from the ResourceHandler given as a pararameter.
     * The second parameter describes the expected size of the sprite tile after
     * scaling.*/
    virtual void
    loadTextures(const ResourceHandler<sf::Texture> &textures_handler) override = 0;

    MovePhase getMovePhase() const;

    MapCoordinates getCurrentMove() const;

    virtual MapCoordinates getPlannedMove() const = 0;

    /* Functions initialising the move */
    virtual void startMove(MapCoordinates new_move);

    virtual void finishMove();

    virtual void reverseMove();

    void simulateMovement(sf::Time elapsed_time);

  protected:
    /* Duration of a move for this type of object */
    const sf::Time move_duration_;

    /* The time that passed from the beginning of the move */
    sf::Time move_time_;

    /* Direction in which the object is moving */

  private:
    MapCoordinates current_move_;

    MovePhase move_phase_;
};

} // namespace bd2

#endif
