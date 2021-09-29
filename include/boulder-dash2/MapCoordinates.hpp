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
    MapCoordinates();

    MapCoordinates(int _r, int _c);

    MapCoordinates(const MapCoordinates &p);

    // ==========================================================================
    // OPERATORS
    // ==========================================================================
    MapCoordinates operator+(const MapCoordinates &p) const;

    MapCoordinates operator-(const MapCoordinates &p) const;

    MapCoordinates &operator+=(const MapCoordinates &p);

    MapCoordinates &operator-=(const MapCoordinates &p);

    MapCoordinates &operator=(const MapCoordinates &p);

    // ==========================================================================
    // COMPARE OPERATORS - compare elements lexicographically
    // ==========================================================================
    bool operator<(const MapCoordinates &p) const;

    bool operator==(const MapCoordinates &p) const;

    bool operator>(const MapCoordinates &p) const;

    bool operator<=(const MapCoordinates &p) const;

    bool operator>=(const MapCoordinates &p) const;

    // ==========================================================================
    // OSTREAM OPERATOR
    // ==========================================================================
    friend std::ostream &operator<<(std::ostream &s, const bd2::MapCoordinates &p);

    // ==========================================================================
    // COORDINATES - row and column number
    // ==========================================================================
    int r;
    int c;
};

// ==============================================================================
std::ostream &operator<<(std::ostream &s, const bd2::MapCoordinates &p);

} // namespace bd2


#endif