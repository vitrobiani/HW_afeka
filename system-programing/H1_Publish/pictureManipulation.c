#include "pictureManipulation.h"
#include "generalFunctions.h"
#include <stdio.h>

void pictureManipulation() {
    int s = 5;
    printf("please enter the size: ");
    //scanf("%d",&s); 

    printf("\n enter the values\n");
    int mat[s][s];
    //getMatValues(s, mat);
    int mat1[s][s]; // helper matrix
    int* pMat = (int*)mat;
    initMat(s, pMat);
    mat[0][0] = 1;
    mat[0][1] = 2;
    mat[0][2] = 3;
    mat[0][3] = 4;
    mat[0][4] = 5;
    mat[1][0] = 6;
    mat[1][1] = 7;
    mat[1][2] = 8;
    mat[1][3] = 9;
    mat[1][4] = 10;
    mat[2][0] = 11;
    mat[2][1] = 12;
    mat[2][2] = 13;
    mat[2][3] = 14;
    mat[2][4] = 15;
    mat[3][0] = 16;
    mat[3][1] = 17;
    mat[3][2] = 18;
    mat[3][3] = 19;
    mat[3][4] = 20;
    mat[3][4] = 21;
    mat[4][0] = 22;
    mat[4][1] = 23;
    mat[4][2] = 24;
    mat[4][3] = 25;
    mat[4][4] = 26;

//    printMat(s, s, mat);
//
//
//    printf("what would you like to do: ");
//    printf("\n1. rotate 90 degrees clockwise\n2. rotate 90 degrees counter "
//         "clockwise\n3. rotate vertically\n4. rotate horizontally\n");
//    int opt = 0;
//    do {
//        scanf("%d", &opt);
//    }while (opt <= 0 || opt > 4);
//
//    switch (opt) {    
//    case 1:
//        picRotateClkWise(s, mat, mat1);
//        printMat(s, s, mat);
//        break;
//    case 2:
//        picRotateCounterClkWise(s, mat, mat1);
//        printMat(s, s, mat);
//        break;
//    case 3:
//        picRotateVertically(s, mat, mat1);
//        printMat(s, s, mat);
//        break;
//    case 4:
//        picRotateHorizontally(s, mat, mat1);
//        printMat(s, s, mat);
//        break;
//    }
}

void picRotateClkWise(int s, int mat[][s], int mat1[][s]){
    int t = 0;
    for (int i = 0; i < s; i++) {
        int k = s-1;
        for (int j = 0; j < s; j++) {
            mat1[i][j] = mat[k--][t];
        }
        t++;
    }
}

void picRotateCounterClkWise(int s, int mat[][s], int mat1[][s]){
    int t = s-1;
    for (int i = 0; i < s; i++) {
        int k = 0;
        for (int j = 0; j < s; j++) {
            mat1[i][j] = mat[k++][t];
        }
        t--;
    }

}

void picRotateVertically(int s, int mat[][s], int mat1[][s]){
    int k = 0;
    for (int i = 0; i < s; i++) {
        int t = s-1;
        for (int j = 0; j < s; j++) {
            mat1[i][j] = mat[k][t--];
        }
        k++;
    }
}

void picRotateHorizontally(int s, int mat[][s], int mat1[][s]){
    int k = s-1;
    for (int i = 0; i < s; i++) {
        int t = 0;
        for (int j = 0; j < s; j++) {
            mat1[i][j] = mat[k][t++];
        }
        k--;
    }

}


