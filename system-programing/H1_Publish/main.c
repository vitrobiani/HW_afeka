#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>

#include "sudoku.h"
//#include "pictureLines.h"
#include "pictureManipulation.h"


int main()
{
    int option = 0;
do {

	//srand((unsigned)12345); //just for testing

	printf("\n\n");
	printf("Please choose one of the following options\n");
	printf("1 - Sudoku\n");
	printf("2 - All Lines\n");
	printf("3 - Picture Manipulation\n");
	printf("-1 - Exit\n");

	scanf("%d", &option);
	
	switch (option)
	{
	case 1:
		sudokuGame();
		break;

	case 2:
//		addLines();
		break;

	case 3:
		pictureManipulation();
		break;

	case -1:
        printf("bye bye :)");
        return 0;
		break;
	}
}while (option != -1);
    return 1;
}
