#include "sim.hpp"
#include "../planners/2d/bug1.hpp"
#include "../planners/2d/bug2.hpp"
#include <iostream>

Sim::Sim() : grid() {
    robot = nullptr;
    planner = nullptr;
    max_iterations = 1000;
}

Sim::Sim(std::size_t x, std::size_t y) : grid(x, y) {
    robot = nullptr;
    planner = nullptr;
    max_iterations = 1000;
}

Sim::Sim(std::size_t x, std::size_t y, int max_iter) : grid(x, y) {
    robot = nullptr;
    planner = nullptr;
    max_iterations = max_iter;
}

Sim::Sim(int max_iter) : grid() {
    robot = nullptr;
    planner = nullptr;
    max_iterations = max_iter;
}

Sim::~Sim() {
    // Clean up dynamically allocated objects
    delete robot;
    cleanupPlanner();
}

void Sim::cleanupPlanner() {
    if (planner != nullptr) {
        delete planner;
        planner = nullptr;
    }
}

void Sim::setPlanner(int planner_type) {
    // Clean up existing planner if any
    cleanupPlanner();
    
    // Ensure robot is initialized
    if (robot == nullptr) {
        robot = new PointRobot(grid.getStart());
    }
    
    // Create the appropriate planner based on type
    switch (planner_type) {
        case 1:
            planner = new Bug1(grid, *robot);
            break;
        default:
            // Default to Bug1 if invalid type
            planner = new Bug1(grid, *robot);
            break;
    }
}

bool Sim::isComplete() const {
    if (planner == nullptr || robot == nullptr) {
        return false;
    }
    return planner->isComplete();
}

void Sim::step() {
    // Initialize robot if not already done
    if (robot == nullptr) {
        robot = new PointRobot(grid.getStart());
    }
    
    // Ensure planner is set (default to Bug1 if not set)
    if (planner == nullptr) {
        setPlanner(1);  // Default to Bug1
    }
    
    // Run one step of simulation
    if (!planner->isComplete()) {
        planner->plan();
        point next_move = planner->getNextMove();
        robot->moveTo(next_move);
    }
}

int Sim::runSim() {
    // Initialize robot if not already done
    if (robot == nullptr) {
        robot = new PointRobot(grid.getStart());
    }
    
    // Ensure planner is set (default to Bug1 if not set)
    if (planner == nullptr) {
        setPlanner(1);  // Default to Bug1
    }
    int iterations = 0;
    // Run simulation loop
    while (!planner->isComplete() && iterations < max_iterations) {
        // std::cout << "Planning..." << std::endl;
        // Update planner with current state
        planner->plan();
        
        // Get next move from planner
        point next_move = planner->getNextMove();
        
        // Move robot to next position
        robot->moveTo(next_move);
        iterations++;
    }
    if(iterations == max_iterations) {
        return -1;
    }
    return 0;
}