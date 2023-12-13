#pragma once

#include <iostream>
#include <array>

class Sudoku {
private:
    std::array<std::array<int, 9>, 9> grid; // Utilisation d'un tableau bidimensionnel de 9*9
    int recursiveCalls = 0; // Nombre d'appels récursifs pour la résolution de la grille

public:
    // Constructeur par défaut initialisant la grille avec des valeurs nulles
    Sudoku();

    // Constructeur avec niveau de complexité pour la génération de la grille
    Sudoku(int complexity);

    // Surcharge de l'opérateur << pour afficher la grille Sudoku
    friend std::ostream& operator<<(std::ostream& os, const Sudoku& sudoku);

    // Méthode helper pour tester si une valeur peut être positionnée dans une case
    bool isSafe(int row, int col, int value) const;

    // Méthode helper pour tester la validité d'une valeur dans une ligne
    bool isValidInRow(int row, int value) const;

    // Méthode helper pour tester la validité d'une valeur dans une colonne
    bool isValidInCol(int col, int value) const;

    // Méthode helper pour tester la validité d'une valeur dans un carré élémentaire
    bool isValidInBox(int row, int col, int value) const;

    // Méthode helper pour trouver la prochaine case vide
    bool findUnassignedLocation(int& row, int& col) const;

    // Méthode helper pour résoudre la grille générée
    bool solve();

    // Getter pour le nombre d'appels récursifs
    int getRecursiveCalls() const;
};
