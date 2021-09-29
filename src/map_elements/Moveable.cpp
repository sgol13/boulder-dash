#include "boulder-dash2/map_elements/Moveable.hpp"

bd2::Moveable::Moveable(Type _type, MapCoordinates _position)
    : MapElement(_type, _position) {}

bool bd2::Moveable::isMoveable() const { return true; }