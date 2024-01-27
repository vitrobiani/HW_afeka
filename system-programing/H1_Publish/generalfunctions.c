#include "generalFunctions.h"
#include <stdio.h>

void initMat(int s, int *mat) {
    for (int i = 0; i < s * s; i++) {
        *mat = 0;
        mat++;
    }
}

void getMatValues(int s, int S, int *mat) {
    int* p;
    for (int i = 0; i < s; i++) {
        for (int j = 0; j < s; j++) {
            p = mat+S*i+j;
            printf("enter the [%d,%d] value\n", i, j);
            scanf("%d", p);
        }
    }
}

void printMat(int s, int* mat) {
    for (int i = 0; i < s; i++) {
        for (int j = 0; j < s; j++) {
            printf("%3d", *(mat+s*i+j));
        }
        printf("\n");
    }
}


