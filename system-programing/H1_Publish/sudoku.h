#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "generalFunctions.h"
#ifndef SUDOKU
#define SUDOKU
#define SIZE 25

void sudokuGame();

int isSqrt(double num);

int getSize();

int checkSudoku(int s, int* mat, int* occurred);

int checkRow(int s, int* mat, int* occurred, int row);

int checkCol(int s, int* mat, int* occurred, int col);

int checkCube(int s, int* mat, int* occurred, int row, int col, int sr) ;
#endif // !SUDOKU
