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
    for(std::size_t i = x; i < x+w; i++) {
        for(std::size_t j = y; j < y+h; j++) {
            layout[i][j].setCell(Cell::CellState::OBSTACLE);
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