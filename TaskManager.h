/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   TaskManager.h
 * Author: shota
 *
 * Created on November 30, 2019, 11:40 AM
 */

#ifndef TASKMANAGER_H
#define TASKMANAGER_H



#include <errno.h>
#include <time.h>

#include "Task.h"

#define API
#define DEFAULT_STACK_ALLOCATION 4
#define TASK_WAIT_TIME 2

#ifdef __cplusplus
extern "C" {
#endif

  struct TaskManager {

    //stack data structure for non-prioritized tasks
    Stack * stack;

    //priority queue structure for task priorities
    heap_t * heap;


    //safely conduct push pop operations
    pthread_mutex_t lock;

    //waiting for new push task
    pthread_cond_t cond_var;
  }


  struct pthread_condattr
  {
    /* Combination of values:
       Bit 0                : flag whether conditional variable will be
                              sharable between processes.
       Bit 1-COND_CLOCK_BITS: Clock ID.  COND_CLOCK_BITS is the number of bits
                              needed to represent the ID of the clock.  */
    int value;
  };


  //The function wich will be with external linkage to thread pool for stack creation
  API Stack * StackNew(int size);


  //push just pushes new task into the queue increasing internal stack size if necessary
  API void Push(Stack * stack, Task * task);

  //(unsafe) push just pushes new task into the queue increasing internal stack size if necessary
  API Task * Pop(Stack * stack);

  //push new task
  API void SafePush(Stack * stack, Task * task);

  /*
    blocking pop waits until there is any task in the Stack
    when new task is added it safely removes and returns new task
    to be processed by thread from thread pool
  */
  API Task * BlockingPop(Stack * stack);


  //disposes stack
  API void Dispose(Stack * stack);

  //update wait_to
  void UpdateWaitTime(Stack * stack);


  int TPpthread_condattr_setclock (pthread_condattr_t *attr, clockid_t clock_id);



#ifdef __cplusplus
}
#endif

#endif /* TASKMANAGER_H */
