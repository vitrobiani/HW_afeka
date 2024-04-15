#include "generalFunctions.h"
#include <stdio.h>
#include <stdlib.h>

void initMat(int *mat, int row, int col) {
    int *p = mat;
    for (int i = 0; i < row * col; i++) {
        *p = 0;
        p++;
    }
}

void getMatValues(int s, int *mat) {
    int *p;
    for (int i = 0; i < s; i++) {
        for (int j = 0; j < s; j++) {
            p = mat + s * i + j;
            printf("enter element %d  %d :  ", i, j);
            scanf("%d", p);
        }
    }
}

void printMat(int s, const int *mat) {
    for (int i = 0; i < s; i++) {
        for (int j = 0; j < s; j++) {
            printf("%5d", *(mat + s * i + j));
        }
        printf("\n");
    }
}

int isSqrt(int num) {
    double sr = sqrt(num);
    if ((sr - (int)sr) == 0) {
        return 1;
    } else {
        return 0;
    }
}

void matTranspose(int s, int *mat) {
    for (int i = 0; i < s; i++) {
        for (int j = i; j < s; j++) {
            swapElemMat(s, mat, i, j, j, i);
        }
    }
}

void swapElemMat(int s, int *mat, int row1, int col1, int row2, int col2) {
    int tmp = *(mat + row2 * s + col2);
    *(mat + row2 * s + col2) = *(mat + row1 * s + col1);
    *(mat + row1 * s + col1) = tmp;
}

void reverseRow(int s, int *mat, int row) {
    for (int i = 0; i < (s / 2); i++) {
        swapElemMat(s, mat, row, i, row, s - i - 1);
    }
}

void reverseCol(int s, int *mat, int col) {
    for (int i = 0; i < (s / 2); i++) {
        swapElemMat(s, mat, i, col, s - i - 1, col);
    }
}

void fillMatRand(int s, int *mat, int max, int min) {
    int *pMat = mat;
    for (int i = 1; i <= s * s; i++) {
        *pMat = min + (rand() %  (max - min + 1));
        pMat++;
    }
}


