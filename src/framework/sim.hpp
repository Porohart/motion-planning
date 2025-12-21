#pragma once

#include "grid.hpp"

class Sim {
    public:
        Sim();
        Sim(std::size_t x, std::size_t y);
        void runSim();
    private:
        Grid grid;
        PointRobot robot;
        Planner planner;
};