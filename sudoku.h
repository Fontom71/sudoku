// Sudoku.h
#pragma once

#include <iostream>

class Sudoku {
private:
    int** grid;
    int size;

public:
    Sudoku(int n);
    ~Sudoku();

    friend std::ostream& operator<<(std::ostream& os, const Sudoku& sudoku);

    bool isValueValid(int value, int x, int y);
    bool isValidPlacement(int value, int x, int y);
    void generateGrid(int complexity);

    bool solve();
    bool solveHelper(int x, int y);
};
