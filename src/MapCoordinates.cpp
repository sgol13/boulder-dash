#include "boulder-dash2/MapCoordinates.hpp"

bd2::MapCoordinates::MapCoordinates() : r(0), c(0) {}

bd2::MapCoordinates::MapCoordinates(int _r, int _c) : r(_r), c(_c) {}

bd2::MapCoordinates::MapCoordinates(const MapCoordinates &p) : r(p.r), c(p.c) {}

bd2::MapCoordinates bd2::MapCoordinates::operator+(const MapCoordinates &p) const {
    return MapCoordinates(r + p.r, c + p.c);
}

bd2::MapCoordinates bd2::MapCoordinates::operator-(const MapCoordinates &p) const {
    return MapCoordinates(r - p.r, c - p.c);
}

bd2::MapCoordinates &bd2::MapCoordinates::operator+=(const MapCoordinates &p) {
    r += p.r;
    c += p.c;
    return *this;
}

bd2::MapCoordinates &bd2::MapCoordinates::operator-=(const MapCoordinates &p) {
    r -= p.r;
    c -= p.c;
    return *this;
}

bd2::MapCoordinates &bd2::MapCoordinates::operator=(const MapCoordinates &p) {
    r = p.r;
    c = p.c;
    return *this;
}

bool bd2::MapCoordinates::operator<(const MapCoordinates &p) const {

    if (r < p.r)
        return true;

    if (r > p.r)
        return false;

    if (c < p.c)
        return true;

    return false;
}

bool bd2::MapCoordinates::operator==(const MapCoordinates &p) const {
    return r == p.r && c == p.c;
}

bool bd2::MapCoordinates::operator>(const MapCoordinates &p) const {
    return p < *this;
}

bool bd2::MapCoordinates::operator<=(const MapCoordinates &p) const {
    return *this < p || *this == p;
}

bool bd2::MapCoordinates::operator>=(const MapCoordinates &p) const {
    return *this > p || *this == p;
}

std::ostream &operator<<(std::ostream &s, const bd2::MapCoordinates &p) {
    return s << "(" << p.r << ", " << p.c << ")";
}