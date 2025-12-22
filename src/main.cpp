#include "sim.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    // Create simulation with default grid (100x100)
    Sim sim;
    
    // Example: Set planner type at runtime
    // 1 = Bug1, 2 = Bug2
    int planner_type = 1;  // Default to Bug1
    
    // You could also get this from command line arguments
    if (argc > 1) {
        planner_type = std::atoi(argv[1]);
    }
    
    // Set the planner dynamically
    sim.setPlanner(planner_type);
    
    // Run the simulation
    sim.runSim();
    
    return 0;
}