#include "Sudoku.h"
#include <random>

Sudoku::Sudoku() {
    // Initialisation de la grille avec des valeurs nulles
    grid.fill({{0, 0, 0, 0, 0, 0, 0, 0, 0}});
}

std::ostream& operator<<(std::ostream& os, const Sudoku& sudoku) {
    for (const auto& row : sudoku.grid) {
        for (int value : row) {
            os << value << " ";
        }
        os << std::endl;
    }
    return os;
}

bool Sudoku::canPlaceValue(int row, int col, int value) const {
    return isValidInRow(row, value) && isValidInCol(col, value) && isValidInSquare(row, col, value);
}

bool Sudoku::isValidInRow(int row, int value) const {
    for (int col = 0; col < 9; ++col) {
        if (grid[row][col] == value) {
            return false;
        }
    }
    return true;
}

bool Sudoku::isValidInCol(int col, int value) const {
    for (int row = 0; row < 9; ++row) {
        if (grid[row][col] == value) {
            return false;
        }
    }
    return true;
}

bool Sudoku::isValidInSquare(int row, int col, int value) const {
    int startRow = 3 * (row / 3);
    int startCol = 3 * (col / 3);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (grid[startRow + i][startCol + j] == value) {
                return false;
            }
        }
    }

    return true;
}

bool Sudoku::isValidPlacement(int row, int col, int value) const {
    return canPlaceValue(row, col, value);
}