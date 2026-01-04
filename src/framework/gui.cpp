#include "gui.hpp"
#include <cmath>

GridVisualizer::GridVisualizer(const Grid& grid, unsigned int window_width, unsigned int window_height)
    : grid(grid), window(sf::VideoMode(window_width, window_height), "Motion Planning Visualization") {
    
    // Calculate cell size based on grid dimensions and window size
    cell_width = window_width / grid.getWidth();
    cell_height = window_height / grid.getHeight();
    
    // Set colors
    empty_color = sf::Color(255, 255, 255);      // White for empty cells
    obstacle_color = sf::Color(0, 0, 0);         // Black for obstacles
    start_color = sf::Color(0, 255, 0);          // Green for start
    goal_color = sf::Color(255, 0, 0);           // Red for goal
    robot_color = sf::Color(0, 0, 255);           // Blue for robot
    grid_line_color = sf::Color(200, 200, 200);  // Light gray for grid lines
    
    window.setFramerateLimit(60);
}

GridVisualizer::~GridVisualizer() {
    if (window.isOpen()) {
        window.close();
    }
}

void GridVisualizer::render(const PointRobot& robot) {
    window.clear(sf::Color(240, 240, 240)); // Light gray background
    
    // Draw all cells
    for (std::size_t x = 0; x < grid.getWidth(); x++) {
        for (std::size_t y = 0; y < grid.getHeight(); y++) {
            sf::Color cell_color = empty_color;
            
            // Check if this is the start position
            point start = grid.getStart();
            if (x == start.x && y == start.y) {
                cell_color = start_color;
            }
            // Check if this is the goal position
            else {
                point goal = grid.getGoal();
                if (x == goal.x && y == goal.y) {
                    cell_color = goal_color;
                }
                // Check if it's an obstacle
                else if (grid.isObstacle(x, y)) {
                    cell_color = obstacle_color;
                }
            }
            
            drawCell(x, y, cell_color);
        }
    }
    
    // Draw robot position on top of everything
    point robot_pos = robot.getPosition();
    if (grid.isValidCell(robot_pos)) {
        drawCell(robot_pos.x, robot_pos.y, robot_color);
    }
    
    // Draw grid lines
    drawGrid();
    
    window.display();
}

bool GridVisualizer::isOpen() const {
    return window.isOpen();
}

bool GridVisualizer::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
            return true; // Window should close
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                window.close();
                return true;
            }
        }
    }
    return false; // Window should stay open
}

void GridVisualizer::close() {
    window.close();
}

void GridVisualizer::drawCell(std::size_t x, std::size_t y, sf::Color color) {
    sf::RectangleShape cell(sf::Vector2f(cell_width, cell_height));
    sf::Vector2f pixel_pos = gridToPixel(x, y);
    cell.setPosition(pixel_pos);
    cell.setFillColor(color);
    cell.setOutlineThickness(0);
    window.draw(cell);
}

void GridVisualizer::drawGrid() {
    // Draw vertical lines
    for (std::size_t x = 0; x <= grid.getWidth(); x++) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(x * cell_width, 0), grid_line_color),
            sf::Vertex(sf::Vector2f(x * cell_width, grid.getHeight() * cell_height), grid_line_color)
        };
        window.draw(line, 2, sf::Lines);
    }
    
    // Draw horizontal lines
    for (std::size_t y = 0; y <= grid.getHeight(); y++) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(0, y * cell_height), grid_line_color),
            sf::Vertex(sf::Vector2f(grid.getWidth() * cell_width, y * cell_height), grid_line_color)
        };
        window.draw(line, 2, sf::Lines);
    }
}

sf::Vector2f GridVisualizer::gridToPixel(std::size_t x, std::size_t y) const {
    return sf::Vector2f(x * cell_width, y * cell_height);
}

