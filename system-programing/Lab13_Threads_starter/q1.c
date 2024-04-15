/*
 * q1.c
 *
 *  Created on: Dec 30, 2018
 *      Author: efrath
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <math.h>

#include "q1.h"


int HandlePrime(int threadsCount,int start,int end)
{
	pthread_t* threads;
	ThreadData* thread_args;
	pthread_mutex_t bufLock;

	int i,sum =0;
	int result_code;

	int delta = (end-start)/threadsCount;

	pthread_mutex_init(&bufLock,NULL);

	//create all threads one by one



	printf("IN MAIN: All threads are created.\n");

	//wait for each thread to complete
	for (i = 0; i < threadsCount; i++) {
		result_code = pthread_join(threads[i], NULL);
		assert(!result_code);
		printf("IN MAIN: Thread %d has ended.\n", i);
	}

	printf("HandlePrime has ended.\n");
	return sum;
}

void* perform_work_sync(void *arguments){




	return NULL;

}

int isPrime(int num)
{
	int i;

	if(num == 1)
		return 1;

	for(i = 2; i <= sqrt(num); i++)
	{
		if(num%i == 0)
			return 0;
	}

	return 1;
}
