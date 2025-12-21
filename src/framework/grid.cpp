#include "grid.hpp"

Grid::Grid() {
    w = 100;
    h = 100;
    layout.resize(w);
    for(std::size_t i = 0; i < w; i++) {
        layout[i].resize(h);
    }
}

Grid::Grid(std::size_t width, std::size_t height) : w(width), h(height) {
    layout.resize(w);
    for(std::size_t i = 0; i < w; i++) {
        layout[i].resize(h);
    }
}

// this places an obstacle of width w, height h with a top left corner at (x, y);
void Grid::placeObstacle(std::size_t w, std::size_t h, std::size_t x, std::size_t y) {
    // bounds checking: clamp obstacle to fit within grid
    std::size_t endX = (x + w > this->w) ? this->w : x + w;
    std::size_t endY = (y + h > this->h) ? this->h : y + h;
    
    // only process if starting position is within bounds
    if(x < this->w && y < this->h) {
        for(std::size_t i = x; i < endX; i++) {
            for(std::size_t j = y; j < endY; j++) {
                layout[i][j].setCell(Cell::CellState::OBSTACLE);
            }
        }
    }
}

// places an obstacle at each point in the provided vector (for arbitrary shapes)
void Grid::placeObstacle(const std::vector<point>& cells) {
    for(const point& p : cells) {
        // bounds checking
        if(p.x < w && p.y < h) {
            layout[p.x][p.y].setCell(Cell::CellState::OBSTACLE);
        }
    }
}

void Grid::setStart(std::size_t x, std::size_t y) {
    start.x = x;
    start.y = y;
}

void Grid::setGoal(std::size_t x, std::size_t y) {
    goal.x = x;
    goal.y = y;
}

// Accessor methods for robot queries
point Grid::getStart() const {
    return start;
}

point Grid::getGoal() const {
    return goal;
}

bool Grid::isObstacle(std::size_t x, std::size_t y) const {
    if(!isValidCell(x, y)) {
        return false;
    }
    return layout[x][y].isObstacle();
}

bool Grid::isObstacle(const point& p) const {
    return isObstacle(p.x, p.y);
}

bool Grid::isValidCell(std::size_t x, std::size_t y) const {
    return x < w && y < h;
}

bool Grid::isValidCell(const point& p) const {
    return isValidCell(p.x, p.y);
}

std::size_t Grid::getWidth() const {
    return w;
}

std::size_t Grid::getHeight() const {
    return h;
}