#include <stdio.h>
#ifndef FUNCTIONSLAB2
#define FUNCTIONSLAB2


int arrGoUp(int arr[], int len)
{
    int f = arr[0];
    for (int i = 1; i < len; i++) {
        if (arr[i] <= f) return 0;
        f = arr[i];
    }
    return 1;
}


#endif
