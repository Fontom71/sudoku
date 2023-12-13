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

    // Le niveau de complexité détermine le nombre de cases pré-remplies, plus la complexité est élevée, moins il y a de cases pré-remplies
    int minFilledCells = 20 - complexity * 5;
    int maxFilledCells = 30 - complexity * 5;

    std::uniform_int_distribution<int> cellsDist(minFilledCells, maxFilledCells);

    int filledCells = cellsDist(gen);

    // Génération des cases pré-remplies
    for (int i = 0; i < filledCells; i++) {
        int row = dist(gen) - 1;
        int col = dist(gen) - 1;
        int value = dist(gen);

        // Assurez-vous que la valeur générée est valide dans la ligne, la colonne et le carré
        if (isSafe(row, col, value)) {
            grid[row][col] = value;
        } else {
            // Si la valeur n'est pas valide, réessayez avec une nouvelle valeur
            i--;
        }
    }
}

std::ostream& operator<<(std::ostream& os, const Sudoku& sudoku) {
    // Affichage de la grille et encadrement des carrés élémentaires
    for (int row = 0; row < 9; row++) {
        if (row % 3 == 0) {
            os << " -----------------------" << std::endl;
        }
        for (int col = 0; col < 9; col++) {
            if (col % 3 == 0) {
                os << "| ";
            }
            os << sudoku.grid[row][col] << " ";
        }
        os << "|" << std::endl;
    }
    os << " -----------------------" << std::endl;

    return os;
}

bool Sudoku::isSafe(int row, int col, int value) const {
    return isValidInRow(row, value) && isValidInCol(col, value) && isValidInBox(row, col, value);
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

bool Sudoku::isValidInBox(int row, int col, int value) const {
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

bool Sudoku::solve()
{
    recursiveCalls++;
    int row, col;

    // Si la grille est complétée, on a terminé
    if (!findUnassignedLocation(row, col)) {
        return true;
    }

    // On teste les valeurs de 1 à 9
    for (int value = 1; value <= 9; ++value) {
        // Si la valeur est valide, on l'assigne à la case
        if (isSafe(row, col, value)) {
            grid[row][col] = value;

            // On récursive sur le reste de la grille
            if (solve()) {
                return true;
            }

            // Si la récursion échoue, on réinitialise la case
            grid[row][col] = 0;
        }
    }

    // Si aucune valeur n'est valide, on retourne false
    return false;
}

bool Sudoku::findUnassignedLocation(int& row, int& col) const {
    for (row = 0; row < 9; ++row) {
        for (col = 0; col < 9; ++col) {
            if (grid[row][col] == 0) {
                return true;
            }
        }
    }
    return false;
}

int Sudoku::getRecursiveCalls() const {
    return recursiveCalls;
}