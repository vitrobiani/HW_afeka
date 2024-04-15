#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "exe.h"
#include "functions.h"
#include "arrays.h"
#include "family.h"
#include "building.h"

int Q1(int opt)
{
//	int size, newSize = 0;
//	int* startArr = NULL;
//	int* newArr = NULL;
//
//	do {
//		printf("Enter size of array: ");
//		scanf("%d", &size);
//	} while (size <= 0);
//
//	//add code to allocate startArr
//
//	initArray(startArr, size);
//	printf("The array is:\t");
//	printArray(startArr, size);
//
//	if (opt == 1)
//	{
//		//call getEvenNumbers_OnePass
//	}
//	else {
//		//call getEvenNumbers_TwoPass
//	}
//
	//Add free where needed!!!!!!!!!!!!!!
	//print result
	



	return 1;
}


int	Q2()
{
	//char* longStr = NULL;

	//call createCombineStrings

	//Add what is needed to show string and free

	return 1;
}


int	Q3()
{
	Family* f1 = (Family*) malloc(sizeof(Family));
	if (!initFamily(f1))
		printf("Error\n");
	else {
		printFamily(f1);
		addPersonToFamily(f1);
		printf("After add person\n");
		printFamily(f1);
		freeFamily(f1);
	}

	//Building b;
	//initBuilding(&b);
	//for (int i = 0; i < b.maxFamilies; i++)
	//{
	//	addFamily(&b);
	//	addPersonToFamily(b.allFamilies[i]);
	//}
	//printf("Building is!!!\n");
	//printBuilding(&b);
	//freeBuilding(&b);
	return 1;


}
