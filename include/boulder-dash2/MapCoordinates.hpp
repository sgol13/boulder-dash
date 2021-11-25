// Szymon Golebiowski
// Boulder Dash 2, 2021

#ifndef BD2_MAP_COORDINATES_HPP
#define BD2_MAP_COORDINATES_HPP

#include "boulder-dash2/defs.hpp"

namespace bd {

/** Class representing coordinates of a tile (map element) on the game map.
 * Coordinates can be negative if they describe object's movement.
 * The first coordinate indicates the row number and the second - the column number.
 * Left-upper corner of the map has coordinates [0, 0]. */
class MapCoordinates {
  public:
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

    constexpr MapCoordinates operator-() { return MapCoordinates(-r, -c); }

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

    constexpr bool operator!=(const MapCoordinates &p) const { return !(*this == p); }

    constexpr bool operator>(const MapCoordinates &p) const { return p < *this; }

    constexpr bool operator<=(const MapCoordinates &p) const {
        return *this < p || *this == p;
    }

    constexpr bool operator>=(const MapCoordinates &p) const {
        return *this > p || *this == p;
    }

    constexpr operator bool() const { return r != 0 || c != 0; }

    // ==========================================================================
    // OSTREAM OPERATOR
    // ==========================================================================
    friend std::ostream &operator<<(std::ostream &s, const bd::MapCoordinates &p) {
        return s << "(" << p.r << ", " << p.c << ")";
    }
    // ==========================================================================
    // COORDINATES - row and column number
    // ==========================================================================
    int r;
    int c;
};

// ==============================================================================
// Typical move directions

constexpr MapCoordinates DIR_CENTER = {0, 0};
constexpr MapCoordinates DIR_UP_LEFT = {-1, -1};
constexpr MapCoordinates DIR_UP = {-1, 0};
constexpr MapCoordinates DIR_UP_RIGHT = {-1, 1};
constexpr MapCoordinates DIR_RIGHT = {0, 1};
constexpr MapCoordinates DIR_DOWN_RIGHT = {1, 1};
constexpr MapCoordinates DIR_DOWN = {1, 0};
constexpr MapCoordinates DIR_DOWN_LEFT = {1, -1};
constexpr MapCoordinates DIR_LEFT = {0, -1};


constexpr std::array<MapCoordinates, 4> DIR_AROUND4 = {DIR_UP, DIR_RIGHT, DIR_DOWN,
                                                       DIR_LEFT};

constexpr std::array<MapCoordinates, 5> DIR_AROUND5 = {DIR_CENTER, DIR_UP, DIR_RIGHT,
                                                       DIR_DOWN, DIR_LEFT};

constexpr std::array<MapCoordinates, 8> DIR_AROUND8 = {
    DIR_UP_LEFT,    DIR_UP,   DIR_UP_RIGHT,  DIR_RIGHT,
    DIR_DOWN_RIGHT, DIR_DOWN, DIR_DOWN_LEFT, DIR_LEFT};

} // namespace bd


#endif