#include "GradientDescent.hpp"
#include <cmath>

GradientDescent::GradientDescent(Grid& grid, PointRobot& robot)
    : Planner(grid, robot) {
    current = robot.getPosition();
    goal = grid.getGoal();
}

void GradientDescent::plan() {
    current = robot.getPosition();
}

point GradientDescent::getNextMove() {
    return current;
}

vector<point> GradientDescent::getObstaclePointsWithinSensorDistance() const {
    vector<point> obstacle_points;
    if(sensor_distance == 0) {
        return obstacle_points;
    }
    for(int square_size = 0; square_size < sensor_distance; square_size++) {
        for(int i = -square_size; i <= square_size; i++) {
            for(int j = -square_size; j <= square_size; j++) {
                point p = current;
                p.x += i;
                p.y += j;
                if(grid.isObstacle(p)) {
                    obstacle_points.push_back(p);
                }
            }
        }
    }
    return obstacle_points;
}

double GradientDescent::getDistanceToGoal() const {
    return std::sqrt(std::pow(current.x - goal.x, 2) + std::pow(current.y - goal.y, 2));
}

double GradientDescent::getDistanceToObstacle(point p) const {
    return std::sqrt(std::pow(p.x - current.x, 2) + std::pow(p.y - current.y, 2));
}

utils::matrix::Vector2d GradientDescent::getGradient() const {
    double distance_to_goal = getDistanceToGoal();
    utils::matrix::Vector2d attractive_force;
    if(distance_to_goal <= attractive_threshold_distance) {
        utils::matrix::Vector2d quadratic_attractive_force((current.x - goal.x)*goal_distance_scaling, (current.y - goal.y)*goal_distance_scaling);
        attractive_force = quadratic_attractive_force;
    } else {
        utils::matrix::Vector2d conic_attractive_force((attractive_threshold_distance*goal_distance_scaling)*((current.x - goal.x)/(distance_to_goal)), (attractive_threshold_distance*goal_distance_scaling)*((current.y - goal.y)/(distance_to_goal)));
        attractive_force = conic_attractive_force;
    }
    vector<point> obstacle_points = getObstaclePointsWithinSensorDistance();
    if(obstacle_points.size() == 0) {
        return attractive_force;
    }
    for(point obstacle_point : obstacle_points) {
        // this line needs to be adjusted, i'm not sure how to make it a vector with distinct x and y components
        utils::matrix::Vector2d repulsive_force((1/2*obstacle_distance_scaling*(1/getDistanceToObstacle(obstacle_point)-1/sensor_distance)), (1/2*obstacle_distance_scaling*(1/getDistanceToObstacle(obstacle_point)-1/sensor_distance)));
    }
}