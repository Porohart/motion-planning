#include "bug1.hpp"
#include "../../framework/utils.hpp"
#include <cmath>
#include <cassert>

Bug1::Bug1(Grid& grid, PointRobot& robot) 
    : Planner(grid, robot), sensor_distance(1) {
    current = robot.getPosition();
    goal = grid.getGoal();
    following_obstacle = false;
}

void Bug1::plan() {
    // Update current position from robot
    current = robot.getPosition();
    goal = grid.getGoal();
    
    // Bug1 algorithm: move toward goal, follow wall if obstacle encountered 
    static bool first_time_encountering_obstacle = true; // this is used to make sure the robot doesnt think it has already looped around the obstacle the first time it encounters it
    if (isAtGoal(current)) {
        return; // Already at goal
    }
    if(!following_obstacle) {
        int x_diff = goal.x - current.x;
        int y_diff = goal.y - current.y;
        double angle = std::atan2(static_cast<double>(y_diff), static_cast<double>(x_diff));
        if(angle > -M_PI/6 && angle <= M_PI/6) {
            next_move.x = current.x + 1;
            next_move.y = current.y;
        } else if(angle > M_PI/6 && angle <= M_PI/3) {
            next_move.x = current.x + 1;
            next_move.y = current.y + 1;
        } else if(angle > M_PI/3 && angle <= 2*M_PI/3) {
            next_move.x = current.x;
            next_move.y = current.y + 1;
        } else if(angle > 2*M_PI/3 && angle <= 5*M_PI/6) {
            next_move.x = current.x - 1;
            next_move.y = current.y + 1;
        } else if(angle > 5*M_PI/6 || angle <= -5*M_PI/6) {
            next_move.x = current.x - 1;
            next_move.y = current.y;
        } else if(angle > -5*M_PI/6 && angle <= -2*M_PI/3) {
            next_move.x = current.x - 1;
            next_move.y = current.y - 1;
        } else if(angle > -2*M_PI/3 && angle <= -M_PI/3) {
            next_move.x = current.x;
            next_move.y = current.y - 1;
        } else if(angle > -M_PI/3 && angle <= -M_PI/6) {
            next_move.x = current.x + 1;
            next_move.y = current.y - 1;
        } else {
            assert(false);
        }
    } else {
        // if currently at the same point as the obstacle encounter point and it is not the first time encountering the obstacle, then the robot has looped around the obstacle
        if(current == obstacle_encounter_point && !first_time_encountering_obstacle) {
            obstacle_looped = true;
        }
        // if the obstacle has been looped and the robot is at the point closest to the goal, then you have finished the obstacle following and can approach the goal linearly
        if(obstacle_looped && current == closest_obstacle_edge_point) { 
            obstacle_looped = false;
            following_obstacle = false;
            next_move = current;
            first_time_encountering_obstacle = true;
            return;
        }
        // determine if the current point is the closest point to the goal seen so far
        double current_distance_to_goal = std::sqrt(std::pow(current.x - goal.x, 2) + std::pow(current.y - goal.y, 2));
        double closest_distance_to_goal = std::sqrt(std::pow(closest_obstacle_edge_point.x - goal.x, 2) + std::pow(closest_obstacle_edge_point.y - goal.y, 2));
        if(current_distance_to_goal < closest_distance_to_goal) {
            closest_obstacle_edge_point = current;
        }
        // follow the wall clockwise by using a local coordinate system to determine the direction of the point to the left of the obstacle
        utils::matrix::Vector2d basis1 = utils::matrix::Vector2d(current, obstacle_point).normalize();
        utils::matrix::Vector2d left_vector = utils::matrix::Vector2d(1, 1);
        utils::matrix::Matrix rotation_matrix = utils::matrix::Matrix(2, 2, {{0, -1}, {1, 0}});
        utils::matrix::Vector2d basis2 = utils::matrix::matMul(rotation_matrix, basis1);
        utils::matrix::Matrix transformation_matrix = utils::matrix::Matrix(2, 2, {{basis1[1][0], basis2[1][0]}, {basis1[2][0], basis2[2][0]}});
        utils::matrix::Vector2d left_dir = utils::matrix::matMul(transformation_matrix, left_vector);
        point next_point = current;
        next_point.x += left_dir[1][0];
        next_point.y += left_dir[2][0];
        if(grid.isObstacle(next_point)) {
            obstacle_point = next_point;
            next_move = current;
        } else {
            if(first_time_encountering_obstacle) {
                first_time_encountering_obstacle = false;
            }
            next_move = next_point;
        }
    }
    if(grid.isObstacle(next_move)) {
        obstacle_encounter_point = current;
        obstacle_point = next_move;
        following_obstacle = true;
        next_move = current;
        closest_obstacle_edge_point = current;
    }
}

point Bug1::getNextMove() {
    return next_move;
}

std::vector<bool> Bug1::getSensorData() {
    std::vector<bool> sensor_data;
    for(int i = -sensor_distance; i <= sensor_distance; i++) {
        for(int j = -sensor_distance; j <= sensor_distance; j++) {
            point p;
            p.x = current.x + i;
            p.y = current.y + j;
            sensor_data.push_back(grid.isObstacle(p));
        }
    }
    return sensor_data;
}