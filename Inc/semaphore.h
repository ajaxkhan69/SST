/*
 * semphore.h
 *
 *  Created on: Nov 17, 2016
 *      Author: tarciso
 */

#ifndef SST_SEMAPHORE_H_
#define SST_SEMAPHORE_H_

#include "math.h"
#include "stdint.h"
#include "sst_stdsignal.h"
#include "uintx.h"
#define NULL_ERROR 0
#define BUSY 1
#define OK 2

typedef struct Sst_semaphore{
	int8_t counter;
	uintX_t waitList;
} Semaphore;

//Semaphore ConstructSemaphore(int8_t c);
Semaphore ConstructSemaphore(int c);
uint8_t do_sem_down(Semaphore *sem, uintX_t prior);
uint8_t do_sem_up(Semaphore *sem);


#endif /* SST_SEMAPHORE_H_ */
