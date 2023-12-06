#include "Sudoku.h"

int main() {
    // Test de la classe Sudoku
    Sudoku sudoku; // Génération de la grille avec un niveau de complexité de 20

    // Affichage de la grille générée
    std::cout << "Generated grid:" << std::endl;
    std::cout << sudoku;

    return 0;
}
