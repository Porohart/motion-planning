#pragma once

#include <cstddef>

struct point {
    std::size_t x;
    std::size_t y;
    
    // Equality operator for point comparison
    bool operator==(const point& other) const {
        return x == other.x && y == other.y;
    }
    
    // Inequality operator (optional but useful)
    bool operator!=(const point& other) const {
        return !(*this == other);
    }
};