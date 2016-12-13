/*
 * uintx.h
 *
 *  Created on: Nov 30, 2016
 *      Author: tarciso
 */

#ifndef SST_UINTX_H_
#define SST_UINTX_H_


#define numberT 64

#if numberT == 8
	typedef uint8_t uintX_t;
	#define ITERATORPRIOR 128
	#define SST_MAX_PRIO 8
#elif numberT == 16
	typedef uint16_t uintX_t;
	#define ITERATORPRIOR 32768
	#define SST_MAX_PRIO 16
#elif numberT == 32
	typedef uint32_t uintX_t;
	#define ITERATORPRIOR  2147483648L
	#define SST_MAX_PRIO 32
#elif numberT == 64
	typedef uint64_t uintX_t;
	#define ITERATORPRIOR 9223372036854775808L
	#define SST_MAX_PRIO 64
#endif

#endif /* SST_UINTX_H_ */
