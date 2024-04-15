#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "generalStrings.h"


char* getStrExactLength()
{
	char* theStr = NULL;
	size_t len;
	char inpStr[MAX_LENGTH]; //variable to hold the string that the user gives

	//Ask for a string from the user
	printf("Enter a String:");
	myGets(inpStr, sizeof(inpStr));

	//find string size and add 1 for the '\0'
	len = strlen(inpStr) + 1;
	//allocate a place for the string in the right location in the array 
	theStr = (char*)malloc(len * sizeof(char));
	//Copy the string to the right location in the array 
	if (theStr != NULL)
		strcpy(theStr, inpStr);

	//can use the strdup function replace line 20 to 25
	//theStr = strdup(inpStr);
	return theStr;
}


char* myGets(char* buffer, int size)
{
	char* ok;
	if (buffer != NULL && size > 0)
	{
		do {
			ok = fgets(buffer, size, stdin);
		} while (ok && ((strlen(buffer) <= 1) && (isspace(buffer[0]))));
		if (ok)
		{
			char* back = buffer + strlen(buffer);
			//trim end spaces
			while ((buffer < back) && (isspace(*--back)));
			*(back + 1) = '\0';
			return buffer;
		}
		buffer[0] = '\0';
	}
	return NULL;
}