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
  printf("%d\n",22);

  return tp;
}


void ThreadPoolStart(ThreadPool * tp) {
  FOR(k,0,tp->size)  {
    tp->threads[k] = (pthread_t*)malloc(sizeof(pthread_t));
    pthread_create(tp->threads[k], NULL, ThreadPoolMainRoutine, tp);
  }
  return;
}

//add new task to thread pool
void PushTask(ThreadPool * tp, Task * task) {
  SafePush(tp->stack,task);
  return;
}

static void * ThreadPoolMainRoutine(void * tp) {
  printf("%s\n","Thread Started");
  //loop while thread not interrupted
  while (!((ThreadPool *)tp)->interrupt_requested) {
    //take next task
    printf("%s\n","Waiting");

    Task * task = BlockingPop(((ThreadPool *)tp)->stack);
    printf("%s\n","TOOOOOK");
    //process task
    if (task != NULL) {
      ProcessTask(task);
      free(task);
    } else return NULL;
  }

  return NULL;
}


void ThreadPoolJoin(ThreadPool * tp) {
  FOR(k,0,tp->size) pthread_join(*(tp->threads[k]),NULL);
  return;
}

//interrupt disposes stack (waking all other threads stuck in pop function)
void ThreadPoolInterrupt(ThreadPool * tp) {
  pthread_mutex_lock(&tp->protect_interrupt);
  if (tp->interrupt_requested == true) {
    pthread_mutex_unlock(&tp->protect_interrupt);
    return;
  }
  tp->interrupt_requested = true;
  Dispose(tp->stack);
  free(tp->stack);

  FOR(k,0,tp->size) free(tp->threads[k]);
  free(tp->threads);
  pthread_mutex_unlock(&tp->protect_interrupt);
  return;
}
