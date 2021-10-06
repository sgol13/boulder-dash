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

    using Map3x3 = std::array<std::array<MapElement::Type, 3>, 3>;

    /** Constructor - as an argument takes the real type of the element
     * and ist initial position (row and column) */
    Moveable(Type _type, const MapCoordinates &_map_position);

    MovePhase getMovePhase() const;

    MapCoordinates getCurrentMove() const;

    virtual MapCoordinates getPlannedMove(const Map3x3 &map3x3) = 0;

    /* Functions initialising the move */
    virtual void startMove(const MapCoordinates &new_move,
                           sf::Time new_move_duration = sf::seconds(0));

    virtual void finishMove();

    virtual void reverseMove();

    void simulateMovement(sf::Time elapsed_time);

    std::vector<MapCoordinates> getAllMapPositions() const override;

    sf::Vector2f getCenterPosition() const;

  protected:
    sf::Time move_duration_;

    /* The time that passed from the beginning of the move */
    sf::Time move_time_;

    /* Direction in which the object is moving */

  private:
    MapCoordinates current_move_;

    MovePhase move_phase_;
};

} // namespace bd2

#endif
