// Szymon Golebiowski
// Boulder Dash

#ifndef BD_BOULDER_HPP
#define BD_BOULDER_HPP

#include "boulder-dash/defs.hpp"
#include "boulder-dash/map_elements/Moveable.hpp"

namespace bd {

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

} // namespace bd

#endif