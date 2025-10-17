#include "cell.hpp"

Cell::Cell() {
    state = CellState::EMPTY;
}

Cell::Cell(CellState start_state) {
    state = start_state;
}

void Cell::setCell(CellState new_state) {
    state = new_state;
}

bool Cell::isEmpty() {
    return state == CellState::EMPTY;
}