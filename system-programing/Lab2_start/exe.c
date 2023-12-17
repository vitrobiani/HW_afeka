#include <stdio.h>
#include "functionsLab2.h"
#include "arrays.h"

void q1_A()
{
    int arr[] = {1,2,3,4,5};
    
    int arrSize = sizeof(arr)/sizeof(arr[0]);

    printf("arr len = %d\n", arrSize);
    printArr(arr, 5);
}

void q1_B()
{
    
    int arrSize = 5;
	
    int* arr = init_arr(arrSize);

    printf("arr len = %d\n", arrSize);
    printArr(arr, arrSize);

}

int checkMatrixForLetter(char mat[][], int row, int col, char dup)
{
    int count;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (mat[i][j] == dup) {
                count++;
            }
        }
    }
    return count;
}

void q2()
{
    char mat[][3] = {{'a','b','c'},{'d','e','f'},{'g','h','i'}};
    
	int c = checkMatrixForLetter(mat, 3, 3, 'a');

    printf("%d\n", c);

}
