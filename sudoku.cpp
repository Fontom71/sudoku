#include "Sudoku.h"
#include <random>

Sudoku::Sudoku() {
    // Initialisation de la grille avec des valeurs nulles
    grid.fill({{0, 0, 0, 0, 0, 0, 0, 0, 0}});
}

Sudoku::Sudoku(int complexity) : Sudoku() {
    // Génération de la grille en fonction du niveau de complexité
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 9);

    // Le niveau de complexité détermine le nombre de cases pré-remplies
    int minFilledCells = 81 - 5 * complexity; // Exemple de formule, ajustez selon vos besoins
    int maxFilledCells = 81 - 4 * complexity; // Exemple de formule, ajustez selon vos besoins

    std::uniform_int_distribution<int> cellsDist(minFilledCells, maxFilledCells);

    int filledCells = cellsDist(gen);

    // Génération des cases pré-remplies
    for (int i = 0; i < filledCells; ++i) {
        int row = dist(gen) - 1;
        int col = dist(gen) - 1;
        int value = dist(gen);

        // Assurez-vous que la valeur générée est valide dans la ligne, la colonne et le carré
        if (isValidPlacement(row, col, value)) {
            grid[row][col] = value;
        } else {
            // Si la valeur n'est pas valide, réessayez avec une nouvelle valeur
            --i;
        }
    }
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