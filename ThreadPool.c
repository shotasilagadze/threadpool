/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "ThreadPool.h"


//initializes thread pool with default thread number 4
ThreadPool * ThreadPoolNew(int size) {
  ThreadPool * tp = (ThreadPool *)malloc(sizeof(ThreadPool));
  tp->size = size;
  tp->stack = StackNew(DEFAULT_STACK_ALLOCATION);
  tp->interrupt_requested = false;
  tp->threads = (pthread_t **)malloc(size*sizeof(pthread_t*));

  return tp;
}


void ThreadPoolStart(ThreadPool * tp) {
  FOR(k,0,tp->size)  pthread_create(tp->threads[k], NULL, ThreadPoolMainRoutine, NULL);
  return;
}


void * ThreadPoolMainRoutine(void * tp) {

  //loop while thread not interrupted
  while (!((ThreadPool *)tp)->interrupt_requested) {
    //take next task
    Task * task = BlockingPop(((ThreadPool *)tp)->stack);
    //process task
    if (task != NULL) Process(task); else return NULL;
  }

  return NULL;
}

static void Process(Task * task) {

}

void ThreadPoolInterrupt(ThreadPool * tp) {
  Dispose(tp->stack);
  tp->interrupt_requested = true;

  return;
}
