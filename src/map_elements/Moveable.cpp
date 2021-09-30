#include "boulder-dash2/map_elements/Moveable.hpp"

bd2::Moveable::Moveable(Type _type, MapCoordinates _position)
    : MapElement(_type, _position), is_moving_(false) {}

bool bd2::Moveable::isMoveable() const { return true; }

sf::Vector2f bd2::Moveable::getOffset() const { return sf::Vector2f(0, 0); }

void bd2::Moveable::moveFrom(MapCoordinates direction) { (void)direction; }

void bd2::Moveable::moveTo(MapCoordinates direction) { (void)direction; }

void bd2::Moveable::simulateMovement(sf::Time elapsed_time) {

    (void)elapsed_time;
    if (is_moving_) {
        // float move_progress
    }
}