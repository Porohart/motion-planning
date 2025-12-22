#include "Planner.hpp"

Planner::Planner(Grid& grid, PointRobot& robot) : grid(grid), robot(robot) {
    current = robot.getPosition();
    goal = grid.getGoal();
}

bool Planner::isComplete() const {
    return isAtGoal(current);
}

bool Planner::isAtGoal(point pos) const {
    return pos == goal;
}

bool Planner::isValidMove(point to) const {
    return grid.isValidCell(to) && !grid.isObstacle(to);
}
