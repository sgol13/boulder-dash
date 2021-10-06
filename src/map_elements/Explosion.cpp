#include "boulder-dash2/map_elements/Explosion.hpp"

bd2::Explosion::Explosion(Type _type, const MapCoordinates &_map_position)
    : MapElement(_type, _map_position), is_finished(false),
      explosion_time_(sf::seconds(0)) {}

void bd2::Explosion::simulateAnimation(sf::Time elapsed_time) {

    explosion_time_ += elapsed_time;
    if (explosion_time_ > EXPLOSION_DURATION) {
        is_finished = true;
    }

    if (is_finished == false) {
        MapElement::simulateAnimation(elapsed_time);
    }
}

bool bd2::Explosion::isFinished() const { return is_finished; }