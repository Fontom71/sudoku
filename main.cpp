// main.cpp
#include "Sudoku.h"
#include <iostream>
#include <cmath>

int main() {
    try {
        // Ask the user for the size of the Sudoku grid
        int gridSize;
        std::cout << "Enter the size of the Sudoku grid (e.g., 9 for 9x9): ";
        std::cin >> gridSize;

        // Validate the size of the Sudoku grid
        if (gridSize <= 0 || gridSize % static_cast<int>(sqrt(gridSize)) != 0) {
            std::cerr << "Error: Invalid grid size. It should be a positive perfect square.\n";
            return 1;
        }

        // Ask the user for the complexity level
        int complexity;
        std::cout << "Enter the complexity level (1 to 5, where 1 is the easiest and 5 is the hardest): ";
        std::cin >> complexity;

        // Validate the complexity level
        if (complexity < 1 || complexity > 5) {
            std::cerr << "Error: Invalid complexity level. It should be between 1 and 5.\n";
            return 1;
        }

        // Create a Sudoku object with the specified grid size
        Sudoku sudoku(gridSize);

        // Generate a Sudoku grid with the specified complexity
        sudoku.generateGrid(complexity);

        // Display the generated grid
        std::cout << "Generated Sudoku Grid:\n" << sudoku << std::endl;

        // Solve the Sudoku grid
        sudoku.solve();

        // Display the solved grid
        std::cout << "Solved Sudoku Grid:\n" << sudoku << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
