#ifndef BD2_MAP_ELEMENTS_HPP
#define BD2_MAP_ELEMENTS_HPP

#include "boulder-dash2/defs.hpp"

namespace map_elements {

enum class Type : int {
    Empty = 0,
    Wall = 1,
    Exit = 2,
    Ground = 3,
    Boulder = 4,
    Diamond = 5,
    Butterfly = 6,
    Firefly = 7,
    Player = 8
};

class MapElement : public sf::Sprite {};

} // namespace map_elements

#endif