#pragma once

#include "../../framework/utils.hpp"

#include <vector>

class PointRobot {
    public:
        PointRobot(point start);
        PointRobot(std::size_t startX, std::size_t startY);
        
        // State access
        point getPosition() const;
        point getStart() const;
        bool isAtStart() const;
        
        // Movement (planner validates moves, robot just executes)
        void moveTo(point p);
        void moveTo(std::size_t x, std::size_t y);
        
        // Path management
        void reset();
        std::vector<point> getPath() const;
        std::size_t getPathLength() const;
        
    private:
        point position;
        std::vector<point> path;
        point startPos;
        
        void initialize();
};

