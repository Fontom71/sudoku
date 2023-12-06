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
