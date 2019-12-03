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



#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Task.h"

#define API
#define DEFAULT_STACK_ALLOCATION 4

#ifdef __cplusplus
extern "C" {
#endif


  /*
   * main stack structure which will store
   * tasks to be processed by thread pool
   */
  typedef struct Stack {
    //measure stack parameters
    int size;
    int alloc_length;

    //stack task array pointer
    Task ** tasks;

    //thread safety parameters
    pthread_mutex_t lock;
    pthread_cond_t cond_var;

    //boolean to show if stack is disposed
    bool disposed;

  } Stack;


  //The function wich will be with external linkage to thread pool for stack creation
  API Stack * StackNew(int size);


  //push just pushes new task into the queue increasing internal stack size if necessary
  API void Push(Stack * stack, Task * task);

  //(unsafe) push just pushes new task into the queue increasing internal stack size if necessary
  API Task * Pop(Stack * stack);

  /*
    blocking pop waits until there is any task in the Stack
    when new task is added it safely removes and returns new task
    to be processed by thread from thread pool
  */
  API Task * BlockingPop(Stack * stack);


  //disposes stack
  API void Dispose(Stack * stack);



#ifdef __cplusplus
}
#endif

#endif /* TASKMANAGER_H */
