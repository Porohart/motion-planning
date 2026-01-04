#include "framework/sim.hpp"
#include "framework/gui.hpp"
#include <SFML/System.hpp>
#include <iostream>

int main(int argc, char* argv[]) {
    // Create simulation
    Sim sim(50, 50);  // 50x50 grid
    
    // IMPORTANT: Set start and goal BEFORE setting planner (planner needs start position)
    sim.getGrid().setStart(5, 5);
    sim.getGrid().setGoal(45, 45);
    
    // Add some obstacles
    sim.getGrid().placeObstacle(10, 10, 20, 20);
    sim.getGrid().placeObstacle(5, 15, 30, 10);
    
    // Set planner (this also initializes the robot at the start position)
    int planner_type = 1;  // Bug1
    if (argc > 1) {
        planner_type = std::atoi(argv[1]);
    }
    sim.setPlanner(planner_type);
    
    // Create GUI visualizer
    GridVisualizer visualizer(sim.getGrid(), 800, 800);
    
    // Run simulation with visualization
    while (visualizer.isOpen() && !sim.isComplete()) {
        // Handle window events
        if (visualizer.handleEvents()) {
            break; // User closed window
        }
        
        // Run one step of simulation
        sim.step();
        
        // Render current state
        visualizer.render(sim.getRobot());
        
        // Small delay to see the animation (optional)
        sf::sleep(sf::milliseconds(50));
    }
    
    // Keep window open until user closes it
    while (visualizer.isOpen()) {
        if (visualizer.handleEvents()) {
            break;
        }
        visualizer.render(sim.getRobot());
        sf::sleep(sf::milliseconds(50));
    }
    
    return 0;
}

