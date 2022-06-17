#include "Cell.h"

// Coordinates

int Dist(const Coordinates& lhs, const Coordinates& rhs) {
    return abs(lhs.x - rhs.x) + abs(lhs.y - rhs.y);
}