#include <stdio.h>

int arrGoUp(int arr[], int len)
{
    int f = arr[0];
    for (int i = 1; i < len; i++) {
        if (arr[i] <= f) return 1;
        f = arr[i];
    }
    return 0;
}


