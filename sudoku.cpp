#include "Sudoku.h"
#include <random>
#include <iomanip>

Sudoku::Sudoku(int N) {
    // Initialisation de la grille avec des valeurs nulles
    grid = std::vector<std::vector<int>>(N, std::vector<int>(N, 0));

    // Génération de la grille
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, N);

    // Génération des cases pré-remplies
    for (int i = 0; i < 30; i++) {
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

Sudoku::Sudoku(int N, int complexity) {
    // Initialisation de la grille avec des valeurs nulles
    grid = std::vector<std::vector<int>>(N, std::vector<int>(N, 0));

    // Génération de la grille
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, grid.size());

    // Le niveau de complexité détermine le nombre de cases pré-remplies, plus la complexité est élevée, moins il y a de cases pré-remplies, par rapport à la taille de la grille, ne dois pas être inférieur à 1
    int minFilledCells = static_cast<int>(std::pow(grid.size(), 2) / 10) * complexity;
    int maxFilledCells = static_cast<int>(std::pow(grid.size(), 2) / 5) * complexity;


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
    int sqrt = std::sqrt(sudoku.grid.size());
    int maxNumWidth = static_cast<int>(std::log10(sudoku.grid.size())) + 1;

    for (int row = 0; row < static_cast<int>(sudoku.grid.size()); row++) {
        if (row % sqrt == 0) {
            for (int i = 0; i < sqrt; i++) {
                os << "+";
                for (int j = 0; j < sqrt * (maxNumWidth + 2) - (sqrt - 1); j++) {
                    os << "-";
                }
            }
            os << "+" << std::endl;
        }
        for (int col = 0; col < static_cast<int>(sudoku.grid.size()); col++) {
            if (col % sqrt == 0) {
                os << "| ";
            }
            os << std::setw(maxNumWidth) << sudoku.grid[row][col] << " ";
        }
        os << "|" << std::endl;
    }
    for (int i = 0; i < sqrt; i++) {
        os << "+";
        for (int j = 0; j < sqrt * (maxNumWidth + 2) - (sqrt - 1); j++) {
            os << "-";
        }
    }
    os << "+" << std::endl;

    return os;
}

bool Sudoku::isSafe(int row, int col, int value) const {
    return isValidInRow(row, value) && isValidInCol(col, value) && isValidInBox(row, col, value);
}

bool Sudoku::isValidInRow(int row, int value) const {
    for (int col = 0; col < static_cast<int>(grid.size()); col++) {
        if (grid[row][col] == value) {
            return false;
        }
    }
    return true;
}

bool Sudoku::isValidInCol(int col, int value) const {
    for (int row = 0; row < static_cast<int>(grid.size()); row++) {
        if (grid[row][col] == value) {
            return false;
        }
    }
    return true;
}

bool Sudoku::isValidInBox(int row, int col, int value) const {
    int sqrtN = std::sqrt(grid.size());
    int startRow = row - row % sqrtN;
    int startCol = col - col % sqrtN;

    for (int i = 0; i < sqrtN; i++) {
        for (int j = 0; j < sqrtN; j++) {
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

    // On teste les valeurs de 1 à la taille de la grille
    for (int value = 1; value <= static_cast<int>(grid.size()); value++) {
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
    for (row = 0; row < static_cast<int>(grid.size()); row++) {
        for (col = 0; col < static_cast<int>(grid.size()); col++) {
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