// Sudoku.cpp
#include "Sudoku.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iomanip>

Sudoku::Sudoku(int n) : size(n) {
    // Initialize the grid with zeros
    grid = new int*[size];
    for (int i = 0; i < size; i++) {
        grid[i] = new int[size];
        for (int j = 0; j < size; j++) {
            grid[i][j] = 0;
        }
    }
}

Sudoku::~Sudoku() {
    for (int i = 0; i < size; i++) {
        delete[] grid[i];
    }
    delete[] grid;
}

std::ostream& operator<<(std::ostream& os, const Sudoku& sudoku) {
    // Affichage de la grille et encadrement des carrés élémentaires
    int sqrt = std::sqrt(sudoku.size);
    std::cout << sudoku.size << std::endl;
    int maxNumWidth = static_cast<int>(std::log10(sudoku.size)) + 1;

    for (int row = 0; row < static_cast<int>(sudoku.size); row++) {
        if (row % sqrt == 0) {
            for (int i = 0; i < sqrt; i++) {
                os << "+";
                for (int j = 0; j < sqrt * (maxNumWidth + 2) - (sqrt - 1); j++) {
                    os << "-";
                }
            }
            os << "+" << std::endl;
        }
        for (int col = 0; col < static_cast<int>(sudoku.size); col++) {
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

bool Sudoku::isValueValid(int value, int x, int y) {
    // Check if the value is present in the same row or column
    for (int i = 0; i < size; i++) {
        if (grid[x][i] == value || grid[i][y] == value) {
            return false;
        }
    }

    // Check if the value is present in the same subgrid
    int subgridSize = static_cast<int>(sqrt(size));
    int startX = x - x % subgridSize;
    int startY = y - y % subgridSize;

    for (int i = 0; i < subgridSize; i++) {
        for (int j = 0; j < subgridSize; j++) {
            if (grid[startX + i][startY + j] == value) {
                return false;
            }
        }
    }

    return true;
}

bool Sudoku::isValidPlacement(int value, int x, int y) {
    return grid[x][y] == 0 && isValueValid(value, x, y);
}

void Sudoku::generateGrid(int complexity) {
        srand(static_cast<unsigned int>(time(nullptr)));

        int minFilledCells = 81 - 10 * complexity;
        int maxFilledCells = 81 - 5 * complexity;
        int filledCells = minFilledCells + rand() % (maxFilledCells - minFilledCells + 1);

        for (int i = 0; i < filledCells; i++) {
            int x = rand() % size;
            int y = rand() % size;
            int value = rand() % size + 1;

            // Keep trying until a valid placement is found or a limit is reached
            int attempts = 0;
            const int maxAttempts = 10;  // Adjust as needed

            while (!isValidPlacement(value, x, y) && attempts < maxAttempts) {
                x = rand() % size;
                y = rand() % size;
                value = rand() % size + 1;
                attempts++;
            }

            if (isValidPlacement(value, x, y)) {
                grid[x][y] = value;
            }
            // If the limit is reached, you may choose to handle it appropriately.
            // For example, break out of the loop or reset the grid and start over.
        }
    }

bool Sudoku::solve() {
    // Dummy code for illustration purposes
    // Start solving from the first cell
    return solveHelper(0, 0);
}

bool Sudoku::solveHelper(int x, int y) {
    // Dummy code for illustration purposes
    // This code simply marks all empty cells as 1
    if (x == size) {
        x = 0;
        if (y++ == size) {
            return true;
        }
    }

    if (grid[x][y] != 0) {
        return solveHelper(x + 1, y);
    }

    for (int value = 1; value <= size; value++) {
        if (isValueValid(value, x, y)) {
            grid[x][y] = value;
            if (solveHelper(x + 1, y)) {
                return true;
            }
        }
    }

    grid[x][y] = 0;
    return false;
}
