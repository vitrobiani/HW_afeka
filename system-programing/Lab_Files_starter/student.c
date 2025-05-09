#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#include "student.h"


void showStudent(Student* st)
{
	printf("%s   %d  %.2f\n", st->name, st->id, st->avg);
}

void showStudentArr(Student* st, int count)
{
	int i;
	for (i = 0; i < count; i++)
		showStudent(&st[i]);
}

void freeStudentArr(Student* stArr, int count)
{
	for(int i = 0; i < count; i++)
		free(stArr[i].name);
	free(stArr);
}


int initStudent(Student* st)
{
	char temp[MAX_LEN];
	printf("Please enter student name, id and avg\n");
	scanf("%s %d %f",temp, &st->id, &st->avg);
	st->name = strdup(temp);
	if (!st->name)
		return 0;
	//st->name = (char*)malloc(sizeof(char)*(strlen(temp) + 1));
	//if (st->name != NULL)
	//	strcpy(st->name, temp);
	//else
	//	return 0;
	return 1;
}

