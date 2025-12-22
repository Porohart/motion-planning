#pragma once

#include "../../framework/grid.hpp"
#include "../../robots/2d/PointRobot.hpp"
#include "../../framework/utils.hpp"

#include <vector>

class Planner {
    public:
        Planner(Grid& grid, PointRobot& robot);
        virtual ~Planner() = default;  // Virtual destructor for proper cleanup
        
        // Main planning method - executes the algorithm
        virtual void plan() = 0;
        virtual point getNextMove() = 0;
        
        // Check if planning is complete (robot reached goal)
        bool isComplete() const;
        
    protected:
        Grid& grid;
        PointRobot& robot;
        point current;
        point goal;
        
        // Helper methods for common planning operations
        bool isValidMove(point to) const;
        bool isAtGoal(point pos) const;
};

