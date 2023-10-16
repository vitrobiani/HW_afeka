#include <stdio.h>
#include "functionsLab2.h"
#include "arrays.h"

void q1_A()
{
    int* arr = init_arr(5);

    for (int i = 1; i <= 5; i++) arr[i-1] = i;
    
    int arrSize = sizeof(arr)/sizeof(arr[0]);

    printf("arr len = %d\n", arrSize);
    printArr(arr, 5);
}

void q1_B()
{
	



}

void q2()
{

	

}

int main(int argc, char *argv[])
{
    q1_A();

    return 0;
}
