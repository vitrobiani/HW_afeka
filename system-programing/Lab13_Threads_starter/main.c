/*
 * main.c
 *
 *  Created on: Dec 30, 2018
 *      Author: efrath
 */

#include <stdio.h>
#include "q1.h"


int main(int argc, char* argv[])
{
	int threadsCount,start,end, total;


	if (argc != 4)
		return 0;
	sscanf(argv[1], "%d", &threadsCount);
	sscanf(argv[2], "%d", &start);
	if(start < 1)
		return 0;

	sscanf(argv[3], "%d", &end);
	if(end < start)
		return 0;


	total = HandlePrime(threadsCount,start,end);
	printf("Total sum = %d\n",total);
	pthread_exit(NULL);
	return 1;
}


