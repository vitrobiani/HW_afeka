#include "person.h"
#ifndef __FAMILY_H
#define __FAMILY_H

typedef struct 
{
	char* familyName;
    Person* theFamily;
    int familySize;
} Family;

int	 initFamily(Family* theFamily);
int  addPersonToFamily(Family* theFamily);
void printFamily(const Family* theFamily);
void freeFamily(Family* theFamily);



#endif // __FAMILY_H
