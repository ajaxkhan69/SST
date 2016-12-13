#include "mytask.h"
#include "stddef.h"
#include "stm32l4xx_hal.h"
#include "usart.h"
#include <stdio.h>

char sendMSG[40] = {0};

void delayNaManha(int delay);


SSTEvent myTask_EQ[myTask_EVQL];
int mytask_counter=0xFF;
void myTask(SSTEvent event , Semaphore *s, MailBox *mb, Queue *q){
	uint8_t exec = do_sem_down(s,myTask_ID);
	
	memset(sendMSG, 0, 40);
	sprintf(sendMSG,"%s ID=%d \n\r",semMSG,myTask_ID);
	HAL_UART_Transmit(&huart4, (uint8_t *)sendMSG, 40, 10000);
	if(exec == OK){
	memset(sendMSG, 0, 40);
	sprintf(sendMSG,"Semaphore Down => ID=%d \n\r",myTask_ID);
	HAL_UART_Transmit(&huart4, (uint8_t *)sendMSG, 40, 10000);

	//SST_post(myTask3_ID,SST_SIGNAL_TASKINIT,0);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);
	delayNaManha(1000);
	do_sem_up(s);

	memset(sendMSG, 0, 40);
	sprintf(sendMSG,"Semaphore Up => ID=%d \n\r",myTask_ID);
	HAL_UART_Transmit(&huart4, (uint8_t *)sendMSG, 40, 10000);
	}else{
		memset(sendMSG, 0, 40);
		sprintf(sendMSG,"Semaphore Busy => ID=%d \n\r",myTask_ID);
		HAL_UART_Transmit(&huart4, (uint8_t *)sendMSG, 40, 10000);
	}
}

SSTEvent myTask2_EQ[myTask2_EVQL];
void myTask2(SSTEvent event , Semaphore *s, MailBox *mb, Queue *q){
	uint8_t exec = do_sem_down(s,myTask2_ID);

memset(sendMSG, 0, 40);
	sprintf(sendMSG,"%s ID=%d \n\r",semMSG,myTask2_ID);
	HAL_UART_Transmit(&huart4, (uint8_t *)sendMSG, 40, 10000);
	if(exec == OK){
	memset(sendMSG, 0, 40);
		sprintf(sendMSG,"Semaphore Down => ID=%d \n\r",myTask2_ID);
		HAL_UART_Transmit(&huart4, (uint8_t *)sendMSG, 40, 10000);
		


		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
		delayNaManha(1000);
		do_sem_up(s);
		memset(sendMSG, 0, 40);
		sprintf(sendMSG,"Semaphore Up => ID=%d \n\r",myTask2_ID);
		HAL_UART_Transmit(&huart4, (uint8_t *)sendMSG, 40, 10000);
	}else{
		memset(sendMSG, 0, 40);
		sprintf(sendMSG,"Semaphore Busy => ID=%d \n\r",myTask2_ID);
		HAL_UART_Transmit(&huart4, (uint8_t *)sendMSG, 40, 10000);
	}
}	


SSTEvent myTask3_EQ[myTask3_EVQL];
void myTask3(SSTEvent event, Semaphore *s, MailBox *mb, Queue *q){

	uint8_t exec = do_sem_down(&mb->s,myTask3_ID);

	memset(sendMSG, 0, 40);
	sprintf(sendMSG,"%s ID=%d \n\r",mbMSG,myTask3_ID);
	HAL_UART_Transmit(&huart4, (uint8_t *)sendMSG, 40, 10000);
	if(exec == OK){
		memset(sendMSG, 0, 40);
		sprintf(sendMSG,"MailBox Down => ID=%d \n\r",myTask3_ID);
		HAL_UART_Transmit(&huart4, (uint8_t *)sendMSG, 40, 10000);

		char msg = 0x03;
		put(mb,msg);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET);
		delayNaManha(1000);

		do_sem_up(&mb->s);

		memset(sendMSG, 0, 40);
		sprintf(sendMSG,"MailBox Up => ID=%d \n\r",myTask3_ID);
		HAL_UART_Transmit(&huart4, (uint8_t *)sendMSG, 40, 10000);
	}else{
		memset(sendMSG, 0, 40);
		sprintf(sendMSG,"MailBox Busy => ID=%d \n\r",myTask3_ID);
		HAL_UART_Transmit(&huart4, (uint8_t *)sendMSG, 40, 10000);

	}

}

SSTEvent myTask4_EQ[myTask4_EVQL];
void myTask4(SSTEvent event, Semaphore *s, MailBox *mb, Queue *q){
	uint8_t exec = do_sem_down(&mb->s,myTask4_ID);
	if(exec == OK){
		char msg = get(mb);
		if(msg == 0x03)
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET);
		do_sem_up(&mb->s);
	}

}


SSTEvent myTask5_EQ[myTask5_EVQL];
void myTask5(SSTEvent event, Semaphore *s, MailBox *mb, Queue *q){

	uint8_t exec = do_sem_down(&q->s,myTask5_ID);

	if(exec == OK){
		char msg = 0x01;
		NODE item;
		item.data  = msg;
		item.prev = NULL;
		Enqueue(q,&item);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET);
		do_sem_up(&q->s);
	}

}

SSTEvent myTask6_EQ[myTask6_EVQL];
void myTask6(SSTEvent event, Semaphore *s, MailBox *mb, Queue *q){
	uint8_t exec = do_sem_down(&q->s,myTask6_ID);
	if(exec == OK){
		NODE *item = Dequeue(q);
		if(item->data == 0x01)
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);
		do_sem_up(&q->s);
	}

}

//HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);
//HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
//

void delayNaManha(int delay){
	int i =0;
	for(i=0; i<delay*1000;i++);
}