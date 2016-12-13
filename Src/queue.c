#include <stdlib.h>
#include "queue.h"
#include "stddef.h"

Queue ConstructQueue(int l, int semaphoreSize){
	Queue q = {.limit = l, .size = 0, .s ={.counter = semaphoreSize}, .head = &(NODE){}, .tail = &(NODE){} };
	return q;
}

void DestructQueue (Queue * q){
	NODE *pN;
	while (!isEmptyQ (q)){
		pN = Dequeue(q);
		free(pN);

	}
	free(q);
}

int Enqueue (Queue *pQueue, NODE *item) {

	if( (pQueue == NULL) || (item == NULL) )
		return FALSE;
	
	if( pQueue->size == pQueue->limit)
		return FALSE;

	if ( pQueue->size == 0 ){
		pQueue->head = item;
		pQueue->tail = item;

	}else {
		//pQueue->head->prev = pQueue->tail;
		pQueue->tail->prev = item;
		pQueue->tail = item;

	}
	pQueue->size++;
	return TRUE;
}

NODE *Dequeue (Queue *pQueue){
	if (isEmptyQ(pQueue))
		return NULL;
	NODE *item = pQueue->head;
	pQueue->head = pQueue->head->prev;
	pQueue->size--;
	return item;
}

int isEmptyQ (Queue *pQueue){
	if(pQueue == NULL){
		return FALSE;
	}
	if(pQueue->size == 0){
		return TRUE;
	} else {
		return FALSE;
	}

}