/*****************************************************************************
* SST platform-independent implementation
*
* Copyright (C) 2006 Miro Samek and Robert Ward. All rights reserved.
*
* This software may be distributed and modified under the terms of the GNU
* General Public License version 2 (GPL) as published by the Free Software
* Foundation and appearing in the file GPL.TXT included in the packaging of
* this file. Please note that GPL Section 2[b] requires that all works based
* on this software must also be made publicly available under the terms of
* the GPL ("Copyleft").
*
* Contact information:
* Email:    miro@quantum-leaps.com
* Internet: www.quantum-leaps.com
*****************************************************************************/
#include "sst_port.h"
#include "math.h"

#include "usart.h"
/* Public-scope objects ----------------------------------------------------*/
//uintX_t SST_currPrio_ = (uintX_t)0xFF;              /* current SST priority */
uintX_t SST_currPrio_ = (uintX_t)0;              /* current SST priority */
uintX_t SST_readySet_ = (uintX_t)0;                        /* SST ready-set */

typedef struct TaskCBTag TaskCB;
struct TaskCBTag {
    SSTTask   task__;
    SSTEvent  *queue__;
    uintX_t   end__;
    uintX_t   head__;
    uintX_t   tail__;
    uintX_t   nUsed__;
    uintX_t   mask__;
    Semaphore *s__;
    MailBox   *mb__;
    Queue     *q__;
};

/* Local-scope objects -----------------------------------------------------*/
static TaskCB l_taskCB[SST_MAX_PRIO];
//SST_currPrio_ = (uintX_t) 0;
/*..........................................................................*/
void SST_task(SSTTask task, uintX_t prio, SSTEvent *queue, uintX_t qlen,
              SSTSignal sig, SSTParam par, Semaphore *s, MailBox *mb, Queue *q)
{
    SSTEvent ie;                                    /* initialization event */
    TaskCB *tcb  = &l_taskCB[prio - 1];
    tcb->task__  = task;
    tcb->queue__ = queue;
    tcb->end__   = qlen;
    tcb->head__  = (uintX_t)0;
    tcb->tail__  = (uintX_t)0;
    tcb->nUsed__ = (uintX_t)0;
    tcb->mask__  = (1 << (prio - 1));
    ie.sig = sig;
    ie.par = par;
    tcb->s__ = s;
    tcb->mb__ = mb;
    tcb->q__ = q;
    //tcb->task__(ie,s,mb,q);                                 /* initialize the task */
    tcb->task__(ie,tcb->s__,tcb->mb__,tcb->q__);
}
/*..........................................................................*/
void SST_run(void) {
    SST_start();                                              /* start ISRs */

    SST_INT_LOCK();
    SST_currPrio_ = (uintX_t)0;   /* set the priority for the SST idle loop */
    SST_schedule_();                  /* process all events produced so far */
    SST_INT_UNLOCK();

    while(1){                                         /* the SST idle loop */
        SST_onIdle();                        /* invoke the on-idle callback */
              SST_schedule_();
    }
}
/*..........................................................................*/
uintX_t SST_post(uintX_t prio, SSTSignal sig, SSTParam par) {
    char msg[40] = {0};
    sprintf(msg,"Entrou post => ID= %d \n\r",prio);
    HAL_UART_Transmit(&huart4, (uint8_t *)msg, 40, 10000);

    TaskCB *tcb = &l_taskCB[prio - 1];
    SST_INT_LOCK();
    if (tcb->nUsed__ < tcb->end__) {
        tcb->queue__[tcb->head__].sig = sig;/* insert the event at the head */
        tcb->queue__[tcb->head__].par = par;
        if ((++tcb->head__) == tcb->end__) {
            tcb->head__ = (uintX_t)0;                      /* wrap the head */
        }
        if ((++tcb->nUsed__) == (uintX_t)1) {           /* the first event? */

            SST_readySet_ |= tcb->mask__;   /* insert task to the ready set */
            SST_schedule_();            /* check for synchronous preemption */
        
        sprintf(msg,"Chamou Schedule => SST_RS= %x \n\r",SST_readySet_);
        HAL_UART_Transmit(&huart4, (uint8_t *)msg, 40, 10000);
        }
        HAL_UART_Transmit(&huart4, (uint8_t *)"ERROR_3\n\r", 9, 10000);
        SST_INT_UNLOCK();
        return (uintX_t)1;                     /* event successfully posted */
    }
    else {
        HAL_UART_Transmit(&huart4, (uint8_t *)"ERROR_P\n\r", 9, 10000);
        SST_INT_UNLOCK();
        return (uintX_t)0;              /* queue full, event posting failed */
    }
}
/*..........................................................................*/
uintX_t SST_mutexLock(uintX_t prioCeiling) {
    uintX_t p;
    SST_INT_LOCK();
    p = SST_currPrio_;               /* the original SST priority to return */
    if (prioCeiling > SST_currPrio_) {
        SST_currPrio_ = prioCeiling;              /* raise the SST priority */
    }
    SST_INT_UNLOCK();
    return p;
}
/*..........................................................................*/
void SST_mutexUnlock(uintX_t orgPrio) {
    SST_INT_LOCK();
    if (orgPrio < SST_currPrio_) {
        SST_currPrio_ = orgPrio;    /* restore the saved priority to unlock */
        SST_schedule_();    /* invoke scheduler after lowering the priority */
    }
    SST_INT_UNLOCK();
}
/*..........................................................................*/
/* NOTE: the SST scheduler is entered and exited with interrupts LOCKED */
void SST_schedule_(void) {


    uintX_t pin = SST_currPrio_;               /* save the initial priority */
    uintX_t p = (uintX_t) log2(SST_readySet_);                                          /* the new priority */
                            /* is the new priority higher than the initial? */

    //double d_p = (uintX_t) log2(SST_readySet_);
    //nt pnew = p;
    char msg[40] = {0};
    //sprintf(msg,"SST_schedule_ => p= %3x  > pin = %3x \n\r", d_p,  pin);
    //HAL_UART_Transmit(&huart4, (uint8_t *)msg, 40, 10000);
    //memset(msg,0, 40);
     /* if ((uintX_t)p > (uintX_t)pin){
        sprintf(msg,"SST_schedule_ IN IF \n\r");
        HAL_UART_Transmit(&huart4, (uint8_t *)msg, 40, 10000);
    } */

    while ( p > pin ) {
        memset(msg,0, 40);
        sprintf(msg,"SST_schedule_ IN while %x \n\r", p);
        HAL_UART_Transmit(&huart4, (uint8_t *)msg, 40, 10000);

        TaskCB *tcb  = &l_taskCB[p - 1];
                                          /* get the event out of the queue */
        SSTEvent e = tcb->queue__[tcb->tail__];
        if ((++tcb->tail__) == tcb->end__) {
            tcb->tail__ = (uintX_t)0;
        }
        if ((--tcb->nUsed__) == (uintX_t)0) {/* is the queue becoming empty?*/
            SST_readySet_ &= ~tcb->mask__;     /* remove from the ready set */
        }
        SST_currPrio_ = p;        /* this becomes the current task priority */
        //SST_INT_UNLOCK();                          /* unlock the interrupts */
memset(msg,0, 40);
        sprintf(msg,"SST_schedule_ IN while 03 %x \n\r", p);
        HAL_UART_Transmit(&huart4, (uint8_t *)msg, 40, 10000);
        SSTEvent ie;
        ie.sig = SST_SIGNAL_TASKINIT;
        ie.par = 0;
        tcb->task__(ie,tcb->s__,tcb->mb__,tcb->q__);
                                     /* call the SST task */

memset(msg,0, 40);
        sprintf(msg,"SST_schedule_ IN while 04 %x \n\r", p);
        HAL_UART_Transmit(&huart4, (uint8_t *)msg, 40, 10000);
        //SST_INT_LOCK();            /* lock the interrupts for the next pass */

        p = (uintX_t) log2(SST_readySet_);
    }
    SST_currPrio_ = pin;                    /* restore the initial priority */
}
