#pragma once

#include "Planner.hpp"

class Bug1 : public Planner {
    public:
        Bug1(Grid& grid, PointRobot& robot);
        virtual ~Bug1() = default;
        
        // Override virtual functions from Planner
        virtual void plan() override;
        virtual point getNextMove() override;
    private:
        int sensor_distance;
};