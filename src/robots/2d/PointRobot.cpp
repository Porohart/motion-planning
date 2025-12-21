#include "PointRobot.hpp"

PointRobot::PointRobot(point start) : startPos(start) {
    initialize();
}

PointRobot::PointRobot(std::size_t startX, std::size_t startY) {
    startPos.x = startX;
    startPos.y = startY;
    initialize();
}

void PointRobot::initialize() {
    position = startPos;
    path.clear();
    path.push_back(position);
}

point PointRobot::getPosition() const {
    return position;
}

point PointRobot::getStart() const {
    return startPos;
}

bool PointRobot::isAtStart() const {
    return position.x == startPos.x && position.y == startPos.y;
}

void PointRobot::moveTo(point p) {
    position = p;
    path.push_back(position);
}

void PointRobot::moveTo(std::size_t x, std::size_t y) {
    point p;
    p.x = x;
    p.y = y;
    moveTo(p);
}

void PointRobot::reset() {
    initialize();
}

std::vector<point> PointRobot::getPath() const {
    return path;
}

std::size_t PointRobot::getPathLength() const {
    return path.size();
}

