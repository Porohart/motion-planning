#pragma once

#include "cell.hpp"
#include "utils.hpp"

#include <vector>

class Grid {
    public:
        Grid(std::size_t width, std::size_t height);
        Grid();
        void placeObstacle(std::size_t w, std::size_t h, std::size_t x, std::size_t y);
        void placeObstacle(const std::vector<point>& cells);
        void setStart(std::size_t x, std::size_t y);
        void setGoal(std::size_t x, std::size_t y);
        
        // Accessor methods for robot queries
        point getStart() const;
        point getGoal() const;
        bool isObstacle(std::size_t x, std::size_t y) const;
        bool isObstacle(const point& p) const;
        bool isValidCell(std::size_t x, std::size_t y) const;
        bool isValidCell(const point& p) const;
        std::size_t getWidth() const;
        std::size_t getHeight() const;
    private:
        std::size_t w;
        std::size_t h;
        std::vector<std::vector<Cell>> layout;
        point start;
        point goal;    
};