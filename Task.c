/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Task.h"

//new task creates task and sets necessary attributes
Task * NewTask(void *(*routine)(void *), void * params, enum TASK_MODE mode) {
  Task * task = (Task *)malloc(sizeof(Task));
  task->routine = routine;
  task->params = params;
  task->result = NULL;
  task->mode = mode;
  task->priority = 0;

  pthread_cond_init(&task->cond_var,NULL);
  pthread_mutex_init(&task->lock,NULL);

  return task;
}


//GetResuls is blocking call until task result is ready to be returned;
void * GetResult(Task * task) {
  //just sleep pop operation until there is any task in the stack
  pthread_mutex_lock(&task->lock);
  while (task->result == NULL) pthread_cond_wait(&task->cond_var, &task->lock);
  pthread_mutex_unlock(&task->lock);

  return task->result;
}


//processes task with given routine and parameters
void ProcessTask(Task * task) {

  void * res = task->routine(task->params);
  //make sure to push new task safely
  pthread_mutex_lock(&task->lock);
  task->result = res;
  //notify waiting thread that there is a new task to be processed
  pthread_cond_signal(&task->cond_var);
  pthread_mutex_unlock(&task->lock);

  return;
}
