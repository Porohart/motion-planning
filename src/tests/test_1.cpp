#include "../framework/sim.hpp"
#include <iostream>

int main() {
    Sim sim(1000);
    sim.setPlanner(1);
    int res = sim.runSim();
    if(res < 0) {
        std::cout << "Simulation timed out" << std::endl;
        // return -1;
    } else {
        std::cout << "Simulation completed successfully" << std::endl;
    }
    return 0;
}