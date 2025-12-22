#pragma once

#include "grid.hpp"
#include "../robots/2d/PointRobot.hpp"
#include "../planners/2d/Planner.hpp"

// Forward declarations for planner types
class Bug1;
class Bug2;

class Sim {
    public:
        Sim();
        Sim(std::size_t x, std::size_t y);
        Sim(std::size_t x, std::size_t y, int max_iter);
        Sim(int max_iter);
        ~Sim();  // Destructor to clean up dynamically allocated objects
        
        // Set planner type at runtime (1 for Bug1, 2 for Bug2)
        void setPlanner(int planner_type);
        
        int runSim();
    private:
        Grid grid;
        PointRobot* robot;
        Planner* planner;
        int max_iterations;
        
        // Helper to clean up planner
        void cleanupPlanner();
};