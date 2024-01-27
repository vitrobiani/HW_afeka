#include "sudoku.h"
#include "generalFunctions.h"
#include <stdio.h>
void sudokuGame() {
    int s = getSize();
    printf("the size you chose is: %dx%d\n", s, s);

    int mat[SIZE][SIZE];
    int *pMat = (int*)mat;
    initMat(SIZE, pMat);
    getMatValues(s,SIZE, pMat);

    printMat(SIZE, pMat);
    int occurred[s];

    if (checkSudoku(s, pMat, occurred)) {
        printf("is good");
    } else {
        printf("is not\n");
    }
}

int getSize() {
    double s = 0;
    do {
        printf("please enter the size:  \n");
        scanf("%lf", &s);
    } while (s < 1 || s > 25 || isSqrt(s));

    return (int)s;
}

int isSqrt(double num) {
    double sr = sqrt(num);
    printf("\n %lf \n", sr);
    if ((sr - (int)sr) == 0) {
        return 0;
    } else {
        return 1;
    }
}

int checkSudoku(int s, int *mat, int *occurred) {
    for (int i = 0; i < s; i++) {
        memset(occurred, 0, s * sizeof(int));
        if (!(checkRow(s, mat, occurred, i) && checkCol(s, mat, occurred, i))) {
            return 0;
        }
    }

    int sr = (int)sqrt(s);
    for (int i = 0, k = 0; k < sr; i += sr) {
        for (int j = 0, t = 0; t < sr; j += sr) {
            memset(occurred, 0, s * sizeof(int));
            if (!(checkCube(s, mat, occurred, i, j, sr))) {
                return 0;
            }
            t++;
        }
        k++;
    }
    return 1;
}

int checkRow(int s, int *mat, int *occurred, int row) {
    for (int j = 0; j < s; j++) {
        occurred[(int)*(mat + row * s+ j) - 1] = 1;
    }

    for (int i = 0; i < s; i++) {
        if (occurred[i] == 0) {
            return 0;
        }
    }
    return 1;
}

int checkCol(int s, int *mat, int *occurred, int col) {
    for (int j = 0; j < s; j++) {
        occurred[(int)*(mat + col + s * j) - 1] = 1;
    }

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
            occurred[(int)*(mat + i * s + j) - 1] = 1;
            t++;
        }
        k++;
    }

    for (int i = 0; i < s; i++) {
        if (occurred[i] == 0) {
            return 0;
        }
    }
    return 1;
}
