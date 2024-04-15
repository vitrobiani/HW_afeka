#include "pictureManipulation.h"
#include "generalFunctions.h"
#include <stdio.h>
void pictureManipulation() {
    int s = MAXSIZE;
    printf("Max mat size is: %d\n", MAXSIZE);
    do {
        printf("Insert picture size between 1 and %d\n", MAXSIZE);
        scanf("%d", &s);
    } while (s <= 0 || s > MAXSIZE);
    printf("effecive mat size is: %d\n", s);
    int mat[MAXSIZE][MAXSIZE];
    int *pMat = (int *)mat;

    fillMatRand(s, pMat, MAX, MIN);

    pMat = (int *)mat;
    printMat(s, pMat);
    int opt = 0;
    do {
        printf("\n\nPlease choose one of the following options");
        printf(
            "\n1 - 90 degree clockwise\n2 - 90 degree counter clockwise\n3 - "
            "Flip Horizontal\n4 - Flip Vertical\n-1 - Quit\n");

        scanf("%d", &opt);

        switch (opt) {
        case 1:
            picRotateClkWise(s, pMat);

            break;
        case 2:
            picRotateCounterClkWise(s, pMat);
            break;
        case 3:
            picRotateVertically(s, pMat);
            break;
        case 4:
            picRotateHorizontally(s, pMat);
            break;
        case -1:
            printf("Bye bye\n");
            break;
        default:
            printf("wrong option\n");
        }
        if (opt <= 4 && opt > 0) {
            printf("\n--------- picture after manipulation ---------\n");
            printMat(s, pMat);
        }
    } while (opt != -1);
}

void picRotateClkWise(int s, int *mat) {
    matTranspose(s, mat);
    for (int i = 0; i < s; i++) {
        reverseRow(s, mat, i);
    }
}

void picRotateCounterClkWise(int s, int *mat) {
    matTranspose(s, mat);
    for (int i = 0; i < s; i++) {
        reverseCol(s, mat, i);
    }
}

void picRotateVertically(int s, int *mat) {
    for (int i = 0; i < s; i++) {
        reverseCol(s, mat, i);
    }
}

void picRotateHorizontally(int s, int *mat) {
    for (int i = 0; i < s; i++) {
        reverseRow(s, mat, i);
    }
}
