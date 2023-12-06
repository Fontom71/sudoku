#pragma once

#include <iostream>
#include <array>

class Sudoku {
private:
    std::array<std::array<int, 9>, 9> grid; // Utilisation d'un tableau bidimensionnel de 9*9

public:
    // Constructeur par défaut initialisant la grille avec des valeurs nulles
    Sudoku();

    // Constructeur avec niveau de complexité pour la génération de la grille
    Sudoku(int complexity);

    // Surcharge de l'opérateur << pour afficher la grille Sudoku
    friend std::ostream& operator<<(std::ostream& os, const Sudoku& sudoku);

    // Méthodes helper pour tester la validité d'une valeur
    bool isValidInRow(int row, int value) const;
    bool isValidInCol(int col, int value) const;
    bool isValidInSquare(int row, int col, int value) const;

    // Méthode helper pour résoudre la grille générée
    bool solve();
};
