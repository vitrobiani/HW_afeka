#include <stdio.h>
#include "person.h"


void	initPerson(Person* pPer)
{
    char* name = pPer->name;
	printf("please enter person name\n");
	scanf("%s", name);
	pPer->theType = getTypeFromUser();
	getchar();
}

Type	getTypeFromUser()
{
	int i, t;
	printf("Enter person type\n");
	do {
		for (i = 0; i < NofTypes; i++)
			printf("Enter %d for %s\n", i, typeTilte[i]);
		scanf("%d", &t);
	} while (t < 0 || t >= NofTypes);
	return (Type)t;
}

void	printPerson(const Person* pPer)
{
	printf("%s name %s\n", typeTilte[pPer->theType], pPer->name);
}
