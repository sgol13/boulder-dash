#ifndef BD2_MAP_COORDINATES_HPP
#define BD2_MAP_COORDINATES_HPP

#include "boulder-dash2/defs.hpp"

namespace bd2 {

// ==============================================================================
/** Class representing coordinates of a tile (map element) on the game map.
 * Coordinates can be negative if they describe object's movement.
 * The first coordinate indicates the row numberand the second - the column number.
 * Left-upper corner of the map has coordinates [0, 0]. */
// ==============================================================================
class MapCoordinates {
  public:
    // ==========================================================================
    // CONSTRUCTORS
    // ==========================================================================
    MapCoordinates() : r(0), c(0) {}

    MapCoordinates(int _r, int _c) : r(_r), c(_c) {}

    MapCoordinates(const MapCoordinates &p) : r(p.r), c(p.c) {}

    // ==========================================================================
    // OPERATORS
    // ==========================================================================
    MapCoordinates operator+(const MapCoordinates &p) const {
        return MapCoordinates(r + p.r, c + p.c);
    }

    MapCoordinates operator-(const MapCoordinates &p) const {
        return MapCoordinates(r - p.r, c - p.c);
    }

    MapCoordinates &operator+=(const MapCoordinates &p) {
        r += p.r;
        c += p.c;
        return *this;
    }

    MapCoordinates &operator-=(const MapCoordinates &p) {
        r -= p.r;
        c -= p.c;
        return *this;
    }

    // ==========================================================================
    // OSTREAM OPERATOR
    // ==========================================================================
    friend std::ostream &operator<<(std::ostream &s, const bd2::MapCoordinates &p) {
        return s << "(" << p.r << ", " << p.c << ")";
    }

    // ==========================================================================
    // COORDINATES - row and column number
    // ==========================================================================
    int r;
    int c;
};

} // namespace bd2


#endif