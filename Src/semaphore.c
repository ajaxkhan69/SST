/*
 * semaphore.c
 *
 *  Created on: Nov 17, 2016
 *      Author: tarciso
 */


#include "semaphore.h"
#include "stdlib.h"
#include "sst_port.h"
#include "stddef.h"

Semaphore ConstructSemaphore(int c){
	Semaphore sem = {sem.counter = c , sem.waitList = 0};
	return sem;
}

uint8_t do_sem_down(Semaphore *sem, uintX_t prior){

	if(!sem){
		return NULL_ERROR;
	}


	sem->counter--;
	if(sem->counter < 0){
		sem->waitList |= prior;
		return BUSY;
	}

	return OK;
}

uint8_t do_sem_up(Semaphore *sem){
	sem->counter++;
	if(sem->counter <= 0){

		uintX_t taskPrior = sem->waitList;
		uintX_t p = log2(taskPrior);
		uintX_t iteratorPrior =  ITERATORPRIOR;
		sem->waitList &= ~iteratorPrior;

			SST_INT_LOCK();
			SST_post(p,SST_SIGNAL_TASKINIT,0);
			SST_INT_UNLOCK();
	}

	return OK;

}

