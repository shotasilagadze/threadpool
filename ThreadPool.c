/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "ThreadPool.h"


//initializes thread pool with default thread number 4
ThreadPool * ThreadPoolNew(int size) {
  ThreadPool * tp = (ThreadPool *)malloc(sizeof(ThreadPool));
  tp->interrupt_requested = false;
  tp->task_manager = NewTaskManager();

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

  SafePush(tp->stack, tp->heap, task);
  return;
}

static void * ThreadPoolMainRoutine(void * tp) {
  printf("%s\n","Thread Started");
  //loop while thread not interrupted
  while (!((ThreadPool *)tp)->interrupt_requested) {
    //take next task
    Task * task = BlockingPop((TaskManager *)((ThreadPool *)tp)->task_manager);

    //process task if valid
    if (task != NULL) {
      ProcessTask(task);
      //if task reallocation responsibility is givne free task
      if (task->mode == DETACH) free(task);
    }
  }

  return NULL;
}


void ThreadPoolJoin(ThreadPool * tp) {

  FOR(k,0,tp->size) pthread_join(*(tp->threads[k]),NULL);
  return;
}

//interrupt disposes stack (waking all other threads stuck in pop function)
void ThreadPoolInterrupt(ThreadPool * tp) {
  tp->interrupt_requested = true;
  return;
}


//interrupt disposes stack (waking all other threads stuck in pop function)
void ThreadPoolDispose(ThreadPool * tp) {
  Dispose(tp->stack);
  free(tp->stack);

  FOR(k,0,tp->size) free(tp->threads[k]);
  free(tp->threads);
  free(tp);
  return;
}
