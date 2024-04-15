
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "pictureLines.h"
#include "pictureManipulation.h"
#include "sudoku.h"

int main() {

    char option;
    srand(time(NULL)); // just for testing
    
    do {
        printf("\n\nPlease choose one of the following options\n");
        printf("S/s - Sudoku\n");
        printf("A/a - All Lines\n");
        printf("P/p - Picture Manipulation\n");
        printf("E/e - Exit\n");

        scanf(" %c", &option);

        switch (option) {
        case 'S':
        case 's':
            sudokuGame();
            break;

        case 'A':
        case 'a':
            addLines();
            break;

        case 'P':
        case 'p':
            pictureManipulation();
            break;

        case 'E':
        case 'e':
            break;
        }
    } while (option != 'e' && option != 'E');
}
