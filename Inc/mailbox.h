/*
 * mailbox.h
 *
 *  Created on: Nov 30, 2016
 *      Author: tarciso
 */

#ifndef SST_MAILBOX_H_
#define SST_MAILBOX_H_

#include "semaphore.h"

#define TRUE 1
#define FALSE 0

typedef struct mailBox_t{
	Semaphore s;
	char dataMail;
	uint8_t size;

} MailBox;

MailBox ConstructMailBox();
void DestructMailBox();
int put(MailBox *mailbox,  char data);
char get(MailBox *mailbox);
int isEmpty(MailBox *mailbox);

extern MailBox mb;

#endif /* SST_MAILBOX_H_ */
