// Szymon Golebiowski
// Boulder Dash

#ifndef BD_FLYABLE_HPP
#define BD_FLYABLE_HPP

#include "boulder-dash/defs.hpp"
#include "boulder-dash/map_elements/Moveable.hpp"

namespace bd {

class Flyable : public Moveable {
  public:
    Flyable(Type _type, const MapCoordinates &_map_position);

    virtual void
    loadTextures(const ResourceHandler<sf::Texture> &textures_handler) override;

    virtual void startMove(const MapCoordinates &new_move,
                           sf::Time new_move_duration) override;

    virtual MapCoordinates getPlannedMove(const Map3x3 &map3x3) override;

  private:
    MapCoordinates previous_move_;
};

} // namespace bd

#endif