#pragma once

#include "Planner.hpp"
#include "../../framework/utils.hpp"

class Bug1 : public Planner {
    public:
        Bug1(Grid& grid, PointRobot& robot);
        virtual ~Bug1() = default;
        
        // Override virtual functions from Planner
        virtual void plan() override;
        virtual point getNextMove() override;
    private:
        std::vector<bool> getSensorData();
        int sensor_distance;
        point next_move;
        point obstacle_encounter_point;
        point obstacle_point;
        point closest_obstacle_edge_point;
        bool following_obstacle;
        bool obstacle_looped;
};