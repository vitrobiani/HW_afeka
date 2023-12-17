#include <stdio.h>
#include "functionsLab1.h"

int main()
{
	int base;
	
	helloWorld();
	printf("Please enter a number\n");
	scanf("%d", &base);
	printTriangle(base);
    return 0;
}

