#pragma once

#include "cell.hpp"
#include "utils.hpp"

#include <vector>

class Grid {
    public:
        Grid(std::size_t width, std::size_t height);
        Grid();
        void placeObstacle(std::size_t w, std::size_t h, std::size_t x, std::size_t y);
        void setStart(std::size_t x, std::size_t y);
        void setGoal(std::size_t x, std::size_t y);
    private:
        std::size_t w;
        std::size_t h;
        std::vector<std::vector<Cell>> layout;
        point start;
        point goal;    
};