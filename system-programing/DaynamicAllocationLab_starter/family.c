#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "family.h"
#include "person.h"


int initFamily(Family* theFamily)
{
    char* name = theFamily->familyName;
    printf("please enter the family name: \n");
    scanf("%s", name);
    printf("%s\n", name);
    return 0;
}

int addPersonToFamily(Family* theFamily)
{


	return 0;
}


void printFamily(const Family* theFamily)
{
    printf("these are the family members: \n");

    Person* p = theFamily->theFamily;
    for (int i = 0; i < theFamily->familySize; i++) {
        printPerson(p);
        p++;
        printf("\n");
    }
}

void freeFamily(Family* theFamily)
{




}





