#include "sudoku.h"
#include "generalFunctions.h"
#include <stdio.h>
void sudokuGame() {
    // getting the effective size from the user
    int s = 0;
    do {
        printf(" Enter Sudoku size, sqrt(size) need to be an integer less then "
               "25\n");
        scanf("%d", &s);
    } while (s <= 0 || s > SIZE || !isSqrt(s));

    // setting up the martrix and the helper array
    int mat[SIZE][SIZE];
    int *pMat = (int *)mat;
    initMat(pMat, SIZE, SIZE);
    getMatValues(s, pMat);
    int occurred[s];

    printf("\n");
    printMat(s, pMat);

    if (checkSudoku(s, pMat, occurred)) {
        printf("A valid Sudoku");
    } else {
        printf("Not a valid Sudoku\n");
    }
}

int checkSudoku(int s, int *mat, int *occurred) {
    int isSudokuGood;
    // to check rows and cols
    for (int i = 0; i < s; i++) {
        isSudokuGood =
            (checkRow(s, mat, occurred, i) && checkCol(s, mat, occurred, i));
        if (!isSudokuGood)
            return 0;
    }
    // to check the cubes
    int sr = (int)sqrt(s);
    for (int i = 0, k = 0; k < sr; i += sr) {
        for (int j = 0, t = 0; t < sr; j += sr) {
            memset(occurred, 0, s * sizeof(int));
            isSudokuGood = (checkCube(s, mat, occurred, i, j, sr));
            if (!isSudokuGood)
                return 0;
            t++;
        }
        k++;
    }
    return 1;
}

int checkRow(int s, int *mat, int *occurred, int row) {
    memset(occurred, 0, s * sizeof(int));
    for (int j = 0; j < s; j++) {
        int tmp = *(mat + row * s + j) - 1;
        if (tmp < 0 || tmp >= s)
            return 0; // if not in sudoku range
        *(occurred + tmp) = 1;
    }

    // checking if anything haven't occurred
    for (int i = 0; i < s; i++) {
        if (occurred[i] == 0) {
            return 0;
        }
    }
    return 1;
}

int checkCol(int s, int *mat, int *occurred, int col) {
    memset(occurred, 0, s * sizeof(int));
    for (int j = 0; j < s; j++) {
        int tmp = ((int)*(mat + col + s * j) - 1);
        if (tmp < 0 || tmp >= s)
            return 0; // if not in sudoku range
        *(occurred + tmp) = 1;
    }

    // checking if anything haven't occurred
    for (int i = 0; i < s; i++) {
        if (occurred[i] == 0) {
            return 0;
        }
    }
    return 1;
}

int checkCube(int s, int *mat, int *occurred, int row, int col, int sr) {
    for (int i = row, k = 0; k < sr; i++) {
        for (int j = col, t = 0; t < sr; j++) {
            int tmp = *(mat + i * s + j) - 1;
            if (tmp < 0 || tmp >= s)
                return 0; // if not in sudoku range
            *(occurred + tmp) = 1;
            t++;
        }
        k++;
    }

    // checking if anything haven't occurred
    for (int i = 0; i < s; i++) {
        if (occurred[i] == 0)
            return 0;
    }
    return 1;
}
