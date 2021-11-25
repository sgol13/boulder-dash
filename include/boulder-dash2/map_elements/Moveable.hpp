// Szymon Golebiowski
// Boulder Dash 2, 2021

#ifndef BD2_MOVEABLE_HPP
#define BD2_MOVEABLE_HPP

#include "boulder-dash2/defs.hpp"
#include "boulder-dash2/map_elements/MapElement.hpp"

namespace bd {

class Moveable : public MapElement {
  public:
    enum class MovePhase {
        STANDING, // is not going to do any move
        STARTED_MOVE,
        MOVING,    // is currently moving
        ENDED_MOVE // a move is ended and the procedure should be finished
    };
    // ==========================================================================

    using Map3x3 = std::array<std::array<MapElement::Type, 3>, 3>;

    Moveable(Type _type, const MapCoordinates &_map_position);

    virtual void startMove(const MapCoordinates &new_move,
                           sf::Time new_move_duration = sf::seconds(0));

    virtual void finishMove();

    virtual void reverseMove();

    void simulateMovement(sf::Time elapsed_time);

    MovePhase getMovePhase() const;

    MapCoordinates getCurrentMove() const;

    virtual MapCoordinates getPlannedMove(const Map3x3 &map3x3) = 0;

    std::vector<MapCoordinates> getAllMapPositions() const override;

    /* Returns the coordinates of the center of the object */
    sf::Vector2f getCenterPosition() const;

  protected:
    /* The total duration of the current move */
    sf::Time move_duration_;

    /* The time that passed from the beginning of the move */
    sf::Time move_time_;


  private:
    MapCoordinates current_move_;

    MovePhase move_phase_;
};

} // namespace bd

#endif
