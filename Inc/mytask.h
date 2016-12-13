/*file: mytask.h **********************/
/**************************************/
#ifndef _MYTASK_H_
#define _MYTASK_H_
/*required includes*/
#include "sst.h"
#include "sst_stdsignal.h"
#include "semaphore.h"
#include "mailbox.h"
#include "queue.h"
/*exported macros*/
#define myTask_ID  2
#define myTask2_ID  11
#define myTask3_ID  21
#define myTask4_ID  31
#define myTask5_ID  41
#define myTask6_ID  51

#define myTask_EVQL  4
#define myTask2_EVQL  5
#define myTask3_EVQL  6
#define myTask4_EVQL  7
#define myTask5_EVQL  8
#define myTask6_EVQL  9

#define semMSG "trying to use semaphore => " 
#define mbMSG  "trying to use MailBox => "
#define queMSG "trying to use Queue => " 

#define semMSG "trying to use semaphore => " 
#define mbMSG  "trying to use MailBox => "
#define queMSG "trying to use Queue => " 


/*exported variables*/
extern SSTEvent myTask_EQ[myTask_EVQL];
extern SSTEvent myTask2_EQ[myTask2_EVQL];
extern SSTEvent myTask3_EQ[myTask3_EVQL];
extern SSTEvent myTask4_EQ[myTask4_EVQL];
extern SSTEvent myTask5_EQ[myTask5_EVQL];
extern SSTEvent myTask6_EQ[myTask6_EVQL];



/*exported functions*/
void myTask(SSTEvent event, Semaphore *s, MailBox *mb, Queue *q);
void myTask2(SSTEvent event, Semaphore *s, MailBox *mb, Queue *q);
void myTask3(SSTEvent event, Semaphore *s, MailBox *mb, Queue *q);
void myTask4(SSTEvent event, Semaphore *s, MailBox *mb, Queue *q);
void myTask5(SSTEvent event, Semaphore *s, MailBox *mb, Queue *q);
void myTask6(SSTEvent event, Semaphore *s, MailBox *mb, Queue *q);

#endif
