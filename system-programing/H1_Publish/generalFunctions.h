#include <math.h>
#ifndef GENERALFUNCTIONS
#define GENERALFUNCTIONS

void printMat(int s, const int *mat);

void initMat(int *mat, int row, int col);

void getMatValues(int s, int *mat);

int isSqrt(int num);

void matTranspose(int s, int *mat);

void swapElemMat(int s, int *mat, int row1, int col1, int row2, int col2);

void reverseRow(int s, int *mat, int row);

void reverseCol(int s, int *mat, int col);

void fillMatRand(int s, int *mat, int max, int min);

#endif // !GENERALFUNCTIONS
