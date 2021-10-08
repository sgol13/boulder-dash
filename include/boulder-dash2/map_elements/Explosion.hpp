#ifndef BD2_EXPLOSION_HPP
#define BD2_EXPLOSION_HPP

#include "boulder-dash2/defs.hpp"
#include "boulder-dash2/map_elements/MapElement.hpp"

namespace bd2 {

class Explosion final : public MapElement {
  public:
    Explosion(Type _type, const MapCoordinates &_map_position);

    void simulateAnimation(sf::Time elapsed_time) override;
};

} // namespace bd2

#endif