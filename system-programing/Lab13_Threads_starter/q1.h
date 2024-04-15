/*
 * q1.h
 *
 *  Created on: Dec 30, 2018
 *      Author: efrath
 */

#ifndef Q1_H_
#define Q1_H_
#include <pthread.h>

typedef struct
{
	int id;
	int start;
	int end;
	int* pSum;
	pthread_mutex_t* pMutex;
}ThreadData;


int 	isPrime(int num);
int 	HandlePrime(int threadsCount,int start,int end);
void* 	perform_work_sync(void *arguments);


#endif /* Q1_H_ */
