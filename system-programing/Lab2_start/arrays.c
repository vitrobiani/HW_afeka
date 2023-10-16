#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

void printArr(int arr[], int len){
    for (int i = 0; i < len; i++) {
        printf("%d ", arr[i]);
    }
}

int* init_arr(int len){
    int arr[len];
    return arr;
}

int** init_mat(int col, int row){
    int** mat = malloc(sizeof(int*)*row);
    for (int i = 0; i < row; i++) {
        mat[i] = malloc(sizeof(int)*col);
        for (int j = 0; j < col; j++) {
            mat[i][j] = rand()%50;
        }
    }
    
    return mat;
}

void printMat(int** mat, int row, int col)
{
    for (int i = 0; i < row; i++) {
        //int len = sizeof(mat[i])/sizeof(mat[i][0]);
        for (int j = 0; j < col; j++) {
            printf("%3d ", mat[i][j]); 
        }
        printf("\n");
    }
}

