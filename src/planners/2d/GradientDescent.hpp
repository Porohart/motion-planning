#pragma once

#include "Planner.hpp"

class GradientDescent : public Planner {
    public:
        GradientDescent(Grid& grid, PointRobot& robot);
        virtual ~GradientDescent() = default;
        
        virtual void plan() override;
        virtual point getNextMove() override;
    private:
        vector<point> getObstaclePointsWithinSensorDistance() const;
        double getDistanceToGoal() const;
        double getDistanceToObstacle(point p) const;
        utils::matrix::Vector2d getGradient() const;
        
        int sensor_distance;
        double goal_distance_scaling;
        double obstacle_distance_scaling;
        double attractive_threshold_distance;
};