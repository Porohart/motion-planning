#pragma once

#include "grid.hpp"
#include "../robots/2d/PointRobot.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

class GridVisualizer {
    public:
        GridVisualizer(const Grid& grid, unsigned int window_width = 800, unsigned int window_height = 800);
        ~GridVisualizer();
        
        // Render the current state (includes robot position)
        void render(const PointRobot& robot);
        
        // Check if window is still open
        bool isOpen() const;
        
        // Handle window events (returns true if window should close)
        bool handleEvents();
        
        // Close the window
        void close();
        
    private:
        const Grid& grid;
        sf::RenderWindow window;
        unsigned int cell_width;
        unsigned int cell_height;
        
        // Colors
        sf::Color empty_color;
        sf::Color obstacle_color;
        sf::Color start_color;
        sf::Color goal_color;
        sf::Color robot_color;
        sf::Color grid_line_color;
        
        // Helper methods
        void drawGrid();
        void drawCell(std::size_t x, std::size_t y, sf::Color color);
        sf::Vector2f gridToPixel(std::size_t x, std::size_t y) const;
};

