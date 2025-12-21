#pragma once

#include "../../framework/grid.hpp"
#include "../../robots/2d/PointRobot.hpp"
#include "../../framework/utils.hpp"

#include <vector>

class Planner {
    public:
        Planner(Grid& grid, PointRobot& robot);
        
        // Main planning method - executes the algorithm
        virtual void plan() = 0;
        
        // Check if planning is complete (robot reached goal)
        bool isComplete() const;
        
    protected:
        Grid& grid;
        PointRobot& robot;
        
        // Helper methods for common planning operations
        std::vector<point> getValidNeighbors(point pos) const;
        bool isValidMove(point from, point to) const;
        bool isAtGoal(point pos) const;
        point getGoal() const;
        point getStart() const;
};

