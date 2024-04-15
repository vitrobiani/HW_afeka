#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#include "student.h"


void writeStudentToTextFile(FILE* fp, Student* st)
{
    fprintf(fp, "%s\t%d\t%.2f\n", st->name, st->id, st->avg);
}

int readStudentFromTextFile(FILE* fp, Student* st)
{
	char name[MAX_LEN];
    int id;
    float avg;
    fscanf(fp, "%s\t%d\t%f\n", name, &id, &avg);
    strcpy(st->name, name);
    st->id = id;
    st->avg = avg;

	return  1;
}

int writeStudentArrToTextFile(const char* fileName, Student* stArr, int count)
{
    FILE* fp = fopen(fileName, "w");
    if (fp == NULL)
    {
        return 0;
    }
    int i;
    for (i = 0; i < count; i++)
    {
        writeStudentToTextFile(fp, &stArr[i]);
    }
    fclose(fp);


	return  1;
}


Student* readStudentArrFromTextFile(const char* fileName, int* pCount)
{
    FILE* fp = fopen(fileName, "r");
    if (fp == NULL)
    {
        return NULL;
    }
    char name[MAX_LEN];
    int id;
    float avg;
    int count = 0;
    Student* stArr = (Student*)malloc(sizeof(Student) * 100);
    while (fscanf(fp, "%s\t%d\t%f\n", name, &id, &avg) != EOF)
    {
        strcpy(stArr[count].name, name);
        stArr[count].id = id;
        stArr[count].avg = avg;
        count++;
    }
    fclose(fp);
    *pCount = count;
	
	return NULL;
}

void addStudentToEndOfTextFile(const char* fileName)
{
	



}


