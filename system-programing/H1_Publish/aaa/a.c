#include <stdio.h>
#include <string.h>

void rotate(int s, int mat[][s]) {
    int mat1[s][s];
    for (int i = 0; i < s; i++) {
        for (int j = 0; j < s; j++) {
            mat1[i][j] = 0;
        }
    }
    int t = s - 1;
    for (int i = 0; i < s; i++) {
        int k = 0;
        for (int j = 0; j < s; j++) {
            mat1[i][j] = mat[k++][t];
        }
        t--;
    }

    for (int i = 0; i < s; i++) {
        for (int j = 0; j < s; j++) {
            printf("%3d", mat1[i][j]);
        }
        printf("\n");
    }
}

void func(int *mat) {
    for (int i = 0; i < 9; i++) {
        printf("%5d", *mat);
        mat++;
    }
}
int main(int argc, char *argv[]) {
    // int mat1[][4] = {
    //     {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};

    int mat[3][3];
    //int *pMat = (int*)mat;
    memset(mat, 0, 9 * sizeof(int));
    func(mat);

    // rotate(4, mat1);
    return 0;
}
