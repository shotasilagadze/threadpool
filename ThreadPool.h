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


#define DEFAULT_POOL_SIZE 4

#include "TaskManager.h"
#define STACK_DEFAULT_SIZE 4

#ifdef __cplusplus
extern "C" {
#endif


typedef struct ThreadPool {
  //measure stack parameters
  int size;

  //stack task array pointer
  Stack * stack;


} ThreadPool;


//The function wich creates thread pool
ThreadPool * ThreadPoolNew(int size);



//The function pushes new task to thread pool to be processed;
void PushTask(Task * task);



#ifdef __cplusplus
}
#endif

#endif /* THREADPOOL_H */
