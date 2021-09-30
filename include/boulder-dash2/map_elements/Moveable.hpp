#ifndef BD2_MOVEABLE_HPP
#define BD2_MOVEABLE_HPP

#include "boulder-dash2/defs.hpp"
#include "boulder-dash2/map_elements/MapElement.hpp"

namespace bd2 {

class Moveable : virtual public MapElement {
  public:
    /** Constructor - as an argument takes the real type of the element
     * and ist initial position (row and column) */
    Moveable(Type _type, MapCoordinates _position);

    /* This function is called once a turn to let an object execute its operations */
    virtual void simulate(sf::Time elapsed_time) = 0;

    virtual bool isMoveable() const override;

    /* Returns the vector informing what is the move offset relative to a tile */
    sf::Vector2f getOffset() const;

    /* Functions initialising the move */
    void moveFrom(MapCoordinates direction);

    void moveTo(MapCoordinates direction);

  protected:
    void simulateMovement(sf::Time elapsed_time);

  private:
    /* Flag indicating if the object is currently moving */
    bool is_moving_ = false;

    /* The time that elapsed from the beginning of the move */
    sf::Time move_time_;

    /* Current move offset relative to the tile (in fractions of tile size)  */
    sf::Vector2f move_offset_;

    /* Direction in which the object is moving */
    MapCoordinates move_direction_;
};

} // namespace bd2

#endif
