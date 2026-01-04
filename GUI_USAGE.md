# GUI Visualization Usage

This project includes a GUI visualization using SFML to display the grid, robot position, and goal.

## Installing SFML

### Ubuntu/Debian:
```bash
sudo apt-get install libsfml-dev
```

### macOS (using Homebrew):
```bash
brew install sfml
```

### From Source:
Download from https://www.sfml-dev.org/download.php

## Building with GUI

The Makefile is already configured to link SFML. Just build normally:
```bash
make
```

## Running the GUI

### Option 1: Use the GUI main file
```bash
# Build the GUI version
g++ -std=c++11 -I src -I src/framework -I src/robots/2d -I src/planners/2d \
    src/main_gui.cpp src/framework/*.cpp src/robots/2d/*.cpp src/planners/2d/*.cpp \
    -lsfml-graphics -lsfml-window -lsfml-system -o gui_runner

./gui_runner
```

### Option 2: Integrate into your existing code

```cpp
#include "framework/sim.hpp"
#include "framework/gui.hpp"
#include <SFML/System.hpp>

int main() {
    Sim sim(50, 50);
    sim.getGrid().setStart(5, 5);
    sim.getGrid().setGoal(45, 45);
    sim.getGrid().placeObstacle(10, 10, 20, 20);
    sim.setPlanner(1);
    
    GridVisualizer visualizer(sim.getGrid(), 800, 800);
    
    while (visualizer.isOpen() && !sim.isComplete()) {
        if (visualizer.handleEvents()) break;
        sim.step();
        visualizer.render(sim.getRobot());
        sf::sleep(sf::milliseconds(50));
    }
    
    return 0;
}
```

## Color Scheme

- **White**: Empty cells
- **Black**: Obstacles
- **Green**: Start position
- **Red**: Goal position
- **Blue**: Robot position
- **Light Gray**: Grid lines

## Controls

- **ESC** or **Close Window**: Exit the visualization

