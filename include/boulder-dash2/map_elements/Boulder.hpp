#ifndef BD2_BOULDER_HPP
#define BD2_BOULDER_HPP

#include "boulder-dash2/defs.hpp"
#include "boulder-dash2/map_elements/Moveable.hpp"

namespace bd2 {

class Boulder final : public Moveable {
  public:
    Boulder(Type _type, const MapCoordinates &_map_position);

    MapCoordinates getPlannedMove(const Map3x3 &map3x3,
                                  sf::Time elapsed_time) override;

  private:
    sf::Time left_fall_time_;
    sf::Time center_fall_time_;
    sf::Time right_fall_time_;

    bool is_falling_;
};

} // namespace bd2

#endif