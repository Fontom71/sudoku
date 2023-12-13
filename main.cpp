#include "Sudoku.h"
#include <iostream>
#include <chrono>

int main() {
    // Test de la classe Sudoku
    /*Sudoku sudoku; // Génération de la grille avec un niveau de complexité de 20

    // Affichage de la grille générée
    std::cout << "Grille générée :" << std::endl;
    std::cout << sudoku;

    // Test des nouvelles fonctions
    int testRow = 3;
    int testCol = 4;
    int testValue = 6;

    std::cout << "Test de placement pour la valeur " << testValue
              << " dans la case (" << testRow << ", " << testCol << "): ";

    if (sudoku.isValidPlacement(testRow, testCol, testValue)) {
        std::cout << "Valide." << std::endl;
    } else {
        std::cout << "Invalide." << std::endl;
    }

    // Test de la génération de grilles Sudoku avec différents niveaux de complexité
    for (int complexity = 1; complexity <= 5; ++complexity) {
        Sudoku sudoku(complexity);

        std::cout << "Grille générée avec un niveau de complexité " << complexity << ":" << std::endl;
        std::cout << sudoku;
        std::cout << "--------------------------------------------" << std::endl;
    }*/

    // Test de la résolution de grilles Sudoku avec différents niveaux de complexité
    Sudoku sudokuEasy;
    std::cout << sudokuEasy << std::endl;
    // Résolvez la grille
    if (sudokuEasy.solve()) {
        std::cout << "\nGrille resolue :\n";
        std::cout << sudokuEasy << std::endl;
    } else {
        std::cout << "\nLa grille n'a pas de solution.\n";
    }

    return 0;
}
