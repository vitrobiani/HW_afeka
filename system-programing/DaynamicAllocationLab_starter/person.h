#pragma once

#define LEN 21


typedef enum { Man, Woman, Boy, Girl, NofTypes } Type;
static const char* typeTilte[NofTypes] = {"Man", "Woman", "Boy","Girl" };

typedef struct
{
	char	name[LEN];
	Type	theType;
} Person;


void	initPerson(Person* pPer);
Type	getTypeFromUser();
void	printPerson(const Person* pPer);
