#include "../framework/sim.hpp"
#include <iostream>

int main() {
    utils::matrix::Matrix m(2, 2, {{1, 2}, {3, 4}});
    std::cout << m[0][0] << std::endl;
    std::cout << m[0][1] << std::endl;
    std::cout << m[1][0] << std::endl;
    std::cout << m[1][1] << std::endl;
    return 0;
}