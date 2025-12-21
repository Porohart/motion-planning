#pragma once

class Cell {
    public:
        enum class CellState {
            EMPTY,
            OBSTACLE,
            ROBOT,
            START,
            GOAL
        };
        Cell();
        Cell(CellState start_state);
        void setCell(CellState new_state);
        bool isEmpty() const;
        bool isObstacle() const;
    private:
        CellState state;
};