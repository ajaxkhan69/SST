/*
 * mailbox.c
 *
 *  Created on: Nov 30, 2016
 *      Author: tarciso
 */


#include <stdlib.h>
#include "mailbox.h"
#include "stddef.h"

MailBox ConstructMailBox(){
  MailBox mailbox = {.dataMail = 0, .size = 0, .s = { .counter = 1, .waitList = 0 }};
  return mailbox;
}

void DestructMailBox(MailBox *mailbox){
  while(!isEmpty(mailbox)){
    get(mailbox);
  }
  free(mailbox);
}

int put(MailBox *mailbox, char data){
  if((mailbox == NULL) || (&data == NULL)){
    return FALSE;
  }
  if(mailbox->size >=1){
    return FALSE;
  }

  if(mailbox->size == 0){
    mailbox->dataMail = data;
    mailbox->size++;
  }

  return TRUE;
}

char get(MailBox *mailbox){
  char data = 0x00;
  if(mailbox->size <= 0 ){
    return NULL;
  }
  mailbox->size--;
  data = mailbox->dataMail;
  mailbox->dataMail = NULL;
  return data;
}

int isEmpty(MailBox *mailbox){
  if(mailbox == NULL){
    return FALSE;
  }
  if(mailbox->size == 0){
    return TRUE;
  }else{
    return FALSE;
  }
}
