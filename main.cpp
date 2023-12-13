#include "Sudoku.h"
#include <iostream>
#include <chrono>

int main() {
    // Test de la classe Sudoku
    Sudoku sudoku;

    // Affichage de la grille générée
    std::cout << "Grille generee :" << std::endl;
    std::cout << sudoku;

    // Test des nouvelles fonctions
    int testRow = 3;
    int testCol = 4;
    int testValue = 6;

    std::cout << "Test de placement pour la valeur " << testValue
              << " dans la case (" << testRow << ", " << testCol << "): ";

    if (sudoku.isSafe(testRow, testCol, testValue)) {
        std::cout << "Valide." << std::endl;
    } else {
        std::cout << "Invalide." << std::endl;
    }

    // Test de la résolution de grilles Sudoku avec différents niveaux de complexité
    for (int complexity = 1; complexity <= 5; complexity++) {
        Sudoku sudoku(complexity);

        std::cout << "Grille generee avec un niveau de complexite " << complexity << ":" << std::endl;
        std::cout << sudoku;

        auto start = std::chrono::high_resolution_clock::now();
        if (sudoku.solve()) {
            auto end = std::chrono::high_resolution_clock::now();
            std::cout << "Grille resolue en " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms :" << std::endl;
            std::cout << "Nombre d'appels recursifs : " << sudoku.getRecursiveCalls() << std::endl;
            std::cout << sudoku;
        } else {
            std::cout << "Grille non resolue." << std::endl;
        }
        std::cout << "--------------------------------------------" << std::endl;
    }

    return 0;
}
