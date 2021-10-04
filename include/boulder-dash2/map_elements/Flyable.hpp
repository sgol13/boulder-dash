#ifndef BD2_FLYABLE_HPP
#define BD2_FLYABLE_HPP

#include "boulder-dash2/defs.hpp"
#include "boulder-dash2/map_elements/Moveable.hpp"

namespace bd2 {

class Flyable : public Moveable {
  public:
    /** Constructor - as an argument takes the real type of the element
     * and its initial position (row and column) */
    Flyable(Type _type, MapCoordinates _position);

    /** Loads needed textures from the ResourceHandler given as a pararameter.
     * The second parameter describes the expected size of the sprite tile after
     * scaling.*/
    virtual void
    loadTextures(const ResourceHandler<sf::Texture> &textures_handler) override;

    virtual MapCoordinates getPlannedMove(const Map3x3 &map3x3) const override;

  private:
    MapCoordinates previous_move_;
};

} // namespace bd2

#endif