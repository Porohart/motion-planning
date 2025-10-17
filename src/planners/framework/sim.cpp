#include "sim.hpp"

Sim::Sim() : grid() {
}

Sim::Sim(std::size_t x, std::size_t y) : grid(x, y) {
}

// current empty, i'll think of a good way to implement this
void runSim() { }