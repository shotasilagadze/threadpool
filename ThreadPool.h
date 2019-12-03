/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   ThreadPool.h
 * Author: shotasilagadze
 *
 * Created on December 3, 2019, 12:25 PM
 */

#ifndef THREADPOOL_H
#define THREADPOOL_H


#define API

#include "TaskManager.h"
#include <pthread.h>
#include <stdio.h>

#define FOR(a,b,c) for(int a=b;a<c;a++)


#ifdef __cplusplus
extern "C" {
#endif


typedef struct ThreadPool {
  //measure stack parameters
  int size;

  //stack task array pointer
  Stack * stack;

  //boolean what shows if thread pool is interrupted
  bool interrupt_requested;

  //pthreads array
  pthread_t ** threads;

  //safely interrupt
  pthread_mutex_t protect_interrupt;

} ThreadPool;


//Thread Pool start
void ThreadPoolStart(ThreadPool * tp);

//The function wich creates thread pool
ThreadPool * ThreadPoolNew(int size);

//main thread pool routine which takes tasks from stack and processes
static void * ThreadPoolMainRoutine(void * pt);

//wait until all threads finish execution
void ThreadPoolJoin(ThreadPool * tp);

//interrupt disposes stack (waking all other threads stuck in pop function)
void ThreadPoolInterrupt(ThreadPool * tp);

//add new task
void PushTask(ThreadPool * tp, Task * task);


#ifdef __cplusplus
}
#endif

#endif /* THREADPOOL_H */
