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
    
    // Step mode: true = step through manually, false = auto-run
    bool step_mode = true;
    bool auto_running = false;
    
    // Run simulation with visualization
    while (visualizer.isOpen() && !sim.isComplete()) {
        // Handle window events
        sf::Event event;
        bool should_close = false;
        bool step_requested = false;
        
        while (visualizer.getWindow().pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                should_close = true;
                break;
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    should_close = true;
                    break;
                }
                // Space or Enter to step forward
                if (event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::Enter) {
                    step_requested = true;
                }
                // 'A' to toggle auto-run mode
                if (event.key.code == sf::Keyboard::A) {
                    auto_running = !auto_running;
                    step_mode = !auto_running;
                }
                // 'S' to toggle step mode
                if (event.key.code == sf::Keyboard::S) {
                    step_mode = !step_mode;
                    auto_running = !step_mode;
                }
            }
        }
        
        if (should_close) {
            break;
        }
        
        // Determine if we should step
        bool should_step = false;
        if (auto_running) {
            should_step = true;
        } else if (step_mode && step_requested) {
            should_step = true;
        }
        
        // Step simulation if conditions are met
        if (should_step) {
            sim.step();
        }
        
        // Always render current state
        visualizer.render(sim.getRobot());
        
        // Small delay to see the animation (only in auto mode)
        if (auto_running) {
            sf::sleep(sf::milliseconds(50));
        } else {
            // In step mode, just a tiny delay to keep the window responsive
            sf::sleep(sf::milliseconds(10));
        }
    }
    
    // Keep window open until user closes it
    while (visualizer.isOpen()) {
        sf::Event event;
        bool should_close = false;
        while (visualizer.getWindow().pollEvent(event)) {
            if (event.type == sf::Event::Closed || 
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                should_close = true;
                break;
            }
        }
        if (should_close) {
            break;
        }
        visualizer.render(sim.getRobot());
        sf::sleep(sf::milliseconds(50));
    }
    
    return 0;
}

