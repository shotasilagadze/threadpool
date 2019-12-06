/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Task.h
 * Author: shotasilagadze
 *
 * Created on December 3, 2019, 1:33 PM
 */

#ifndef TASK_H
#define TASK_H

#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

enum TASK_MODE { DETACH, WAIT } ;


typedef struct Task {

  //function which should process tasks
  void *(*routine)(void *);

  //parameter structure pointer
  void * params;

  //result will point to returned value
  void * result;


  //thread safety parameters
  pthread_mutex_t lock;
  pthread_cond_t cond_var;

  //task mode
  enum TASK_MODE mode;

  //task priority used if priority queue is internal data structure
  int priority;

} Task;


//new task creates task and sets necessary attributes
Task * NewTask(void *(*routine)(void *), void * params, enum TASK_MODE mode);

//GetResuls is blocking call until task result is ready to be returned;
void * GetResult(Task * task);

//process task
void ProcessTask(Task * task);


#ifdef __cplusplus
}
#endif

#endif /* TASK_H */
