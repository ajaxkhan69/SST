#ifndef queue_h
#define queue_h

#include <stdint.h>    
#include "semaphore.h"

#define TRUE 1
#define FALSE 0


typedef struct Node_t {
	//uintX_t toPior; 
	char data;
	struct Node_t *prev;
} NODE;

//typedef struct Node_t NODE;
typedef struct Queue_t {
	Semaphore s;
	NODE *head;
	NODE *tail;
	int size;
	int limit;
} Queue;

Queue ConstructQueue(int limit, int semaphoreSize);
void DestructQueue(Queue *q);
int Enqueue(Queue *pQueue, NODE *item);
NODE* Dequeue(Queue *pQueue);
int isEmptyQ(Queue *pQueue);



//extern Queue pQ;

#endif