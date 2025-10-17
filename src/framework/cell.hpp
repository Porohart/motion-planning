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
        bool isEmpty();
    private:
        CellState state;
};