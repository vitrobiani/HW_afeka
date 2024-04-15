#include "pictureLines.h"
#include "generalFunctions.h"
#include <stdio.h>

void addLines() {
    int mat[ROWS][COLS];
    int *pMat = (int *)mat;
    initMat(pMat, ROWS, COLS);
    printf("Mat ROWS: %d , COLS: %d\n", ROWS, COLS);

    int row, col;
    getEffectiveSize(&row, &col);

    printf("Effective size %d*%d\n", row, col);

    int x1, y1, x2, y2;
    int *px1, *py1, *px2, *py2;
    px1 = &x1;
    py1 = &y1;
    px2 = &x2;
    py2 = &y2;
    int isValid = 0;
    int ans = 0;
    int numOfLines = 0;

    do {
        isValid = getLine(row, col, px1, py1, px2, py2);
        if (!isValid) {
            printf("Line paramaters illigal\n");
            printf("Do you want to enter a new line? 1 for yes 0 no\n");
            scanf("%d", &ans);
        } else {
            isValid = !checkIfLineIntercepts(row, col, x1, y1, x2, y2, pMat);
            if (isValid == 0) {
                printf("Line: %d, %d, %d, %d was not inserted to image\n", x1,
                       y1, x2, y2);
                printf("Do you want to enter a new line? 1 for yes 0 no\n");
                scanf("%d", &ans);
            } else {
                insertLine(row, col, x1, y1, x2, y2, pMat);
                numOfLines++;
                printf("Do you want to enter a new line? 1 for yes 0 no\n");
                scanf("%d", &ans);
                if (ans == 1)
                    isValid = 0;
            }
        }

    } while (isValid == 0 && ans == 1);

    printf("Final picture after adding %d lines\n", numOfLines);
    printEMat(row, col, pMat);
}

void getEffectiveSize(int *row, int *col) {
    do {
        printf("Insert number of rows for big Matrix between %d and %d\n", 1,
               ROWS);
        scanf("%d", row);
    } while (*row > ROWS || *row <= 0);
    do {
        printf("Insert number of columns for big Matrix between %d and %d\n",
               1, COLS);
        scanf("%d", col);
    } while (*col > ROWS || *col <= 0);
}

int getLine(int row, int col, int *px1, int *py1, int *px2, int *py2) {
    printf("Insert line parameters x1, y1, x2, y2\n");
    scanf("%d%d%d%d", px1, py1, px2, py2);

    // checking if the line is in effective mat range and is vertical or
    // horizontal
    int isLineNotValid = (*px1 >= col || *px1 < 0) ||
                         (*px2 >= col || *px2 < 0) ||
                         (*py1 >= row || *py1 < 0) || (*py2 >= row || *py2 < 0);
    int arePointsValidOrder = (*px1 <= *px2) && (*py1 <= *py2);
    if ((*px1 != *px2 && *py1 != *py2) || isLineNotValid ||
        !arePointsValidOrder)
        return 0;

    return 1;
}

int checkIfLineIntercepts(int row, int col, int x1, int y1, int x2, int y2, int *mat) {
    for (int i = y1 - 1; i <= y2 + 1; i++) {
        for (int j = x1 - 1; j <= x2 + 1; j++) {
            if (i >= 0 && i < row && j >= 0 && j < col && *(mat + i * col + j) == 1) {
                return 1; // Found a 1 on the line or in its vicinity
            }
        }
    }
    return 0;
}

void insertLine(int row, int col, int x1, int y1, int x2, int y2, int *mat) {
    for (int i = y1; i <= y2; i++) {
        for (int j = x1; j <= x2; j++) {
            *(mat + col * i + j) = 1;
        }
    }
}

void printEMat(int row, int col, const int *mat) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf("%3d", *(mat + col * i + j));
        }
        printf("\n");
    }
}
