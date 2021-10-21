// Szymon Golebiowski
// Boulder Dash 2, 2021

#ifndef BD2_BOULDER_HPP
#define BD2_BOULDER_HPP

#include "boulder-dash2/defs.hpp"
#include "boulder-dash2/map_elements/Moveable.hpp"

namespace bd2 {

class Boulder final : public Moveable {
  public:
    Boulder(Type _type, const MapCoordinates &_map_position);

    void startMove(const MapCoordinates &new_move,
                   sf::Time new_move_duration) override;

    void pushSide(const MapCoordinates &direction);

    MapCoordinates getPlannedMove(const Map3x3 &map3x3) override;

  private:
    sf::Time left_fall_time_;
    sf::Time center_fall_time_;
    sf::Time right_fall_time_;

    bool is_falling_;
    MapCoordinates pushed_direction_;
};

} // namespace bd2

#endif