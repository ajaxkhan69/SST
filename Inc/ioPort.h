/*
 * ioPort.h
 *
 *  Created on: Nov 21, 2016
 *      Author: tarciso
 */

#ifndef SST_IOPORT_H_
#define SST_IOPORT_H_


#include "semaphore.h"



typedef struct Port {
	Semaphore s  ;
	unsigned char ID;
} Port;



#endif /* SST_IOPORT_H_ */
