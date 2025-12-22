#include "bug1.hpp"

Bug1::Bug1(Grid& grid, PointRobot& robot) 
    : Planner(grid, robot), sensor_distance(1) {
    current = robot.getPosition();
    goal = grid.getGoal();
}

void Bug1::plan() {
    // Update current position from robot
    current = robot.getPosition();
    goal = grid.getGoal();
    
    // Bug1 algorithm: move toward goal, follow wall if obstacle encountered
    // This is a simplified implementation
    if (isAtGoal(current)) {
        return; // Already at goal
    }
}

point Bug1::getNextMove() {
    return point{0, 0};
}