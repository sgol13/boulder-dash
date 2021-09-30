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
    constexpr MapCoordinates() : r(0), c(0) {}

    constexpr MapCoordinates(int _r, int _c) : r(_r), c(_c) {}

    constexpr MapCoordinates(const MapCoordinates &p) : r(p.r), c(p.c) {}

    // ==========================================================================
    // OPERATORS
    // ==========================================================================
    constexpr MapCoordinates operator+(const MapCoordinates &p) const {
        return MapCoordinates(r + p.r, c + p.c);
    }

    constexpr MapCoordinates operator-(const MapCoordinates &p) const {
        return MapCoordinates(r - p.r, c - p.c);
    }

    constexpr MapCoordinates &operator+=(const MapCoordinates &p) {
        r += p.r;
        c += p.c;
        return *this;
    }

    constexpr MapCoordinates &operator-=(const MapCoordinates &p) {
        r -= p.r;
        c -= p.c;
        return *this;
    }

    constexpr MapCoordinates &operator=(const MapCoordinates &p) {
        r = p.r;
        c = p.c;
        return *this;
    }

    // ==========================================================================
    // COMPARE OPERATORS - compare elements lexicographically
    // ==========================================================================
    constexpr bool operator<(const MapCoordinates &p) const {

        if (r < p.r)
            return true;

        if (r > p.r)
            return false;

        if (c < p.c)
            return true;

        return false;
    }


    constexpr bool operator==(const MapCoordinates &p) const {
        return r == p.r && c == p.c;
    }

    constexpr bool operator>(const MapCoordinates &p) const { return p < *this; }

    constexpr bool operator<=(const MapCoordinates &p) const {
        return *this < p || *this == p;
    }

    constexpr bool operator>=(const MapCoordinates &p) const {
        return *this > p || *this == p;
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