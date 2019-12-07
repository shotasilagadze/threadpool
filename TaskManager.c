/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "TaskManager.h"

 //The function wich will be with external linkage to thread pool for stack creation
 TaskManager * NewTaskManager() {

   //allocate TaskManager structure
   TaskManager * task_manager = malloc(sizeof(TaskManager));

   //initialize stack data structure
   task_manager->stack = (Stack *)malloc(sizeof(Stack));
   InitializeStack(task_manager->stack);

   //initialize heap
   task_manager->heap = (heap_t *)calloc(1, sizeof (heap_t));
   task_manager->heap->nodes = NULL;


   //initialize conditional variable
   pthread_condattr_t attr;
   pthread_condattr_init( &attr);
   TPpthread_condattr_setclock( &attr, CLOCK_MONOTONIC);
   pthread_cond_init( &task_manager->cond_var, &attr);
   pthread_condattr_destroy(&attr);

   //initialize mutex for save data retrieval
   pthread_mutex_init(&task_manager->lock,NULL);

   return task_manager;
 }





 //push just pushes new task into the queue increasing internal stack size if necessary
 void SafePush(TaskManager * task_manager, Task * task)  {

   //make sure to push new task safely
   pthread_mutex_lock(&task_manager->lock);

   //if priority is assigned insert it into heap
   if (task->priority != 0) push(task_manager->heap, task->priority, (void*)task);
    else StackPush(task_manager->stack, task);

   //notify waiting thread that there is a new task to be processed
   pthread_cond_signal(&task_manager->cond_var);
   pthread_mutex_unlock(&task_manager->lock);

   return;
 }


 /*
   blocking pop waits until there is any task in the Stack
   when new task is added it safely removes and returns new task
   to be processed by thread from thread pool
 */
 Task * BlockingPop(TaskManager * task_manager) {

   pthread_mutex_lock(&task_manager->lock);

   if (task_manager->heap->size != 0) {
     Task * task = (Task *)pop(task_manager->heap);
     pthread_mutex_unlock(&task_manager->lock);
     return task;
   }

   if (task_manager->stack->size != 0) {
     Task * task = (Task *)StackPop(task_manager->stack);
     pthread_mutex_unlock(&task_manager->lock);
     return task;
   }

   //cond var state check
   UpdateWaitTime(task_manager);
   //just sleep pop operation until there is any task in the stack
   pthread_cond_timedwait(&task_manager->cond_var, &task_manager->lock, &task_manager->wait_to);

   //first check priority tasks
   if (task_manager->heap->size != 0) {
     Task * task = (Task *)pop(task_manager->heap);
     pthread_mutex_unlock(&task_manager->lock);
     return task;
   }

   //then check non-priority tasks
   if (task_manager->stack->size != 0) {
     Task * task = (Task *)StackPop(task_manager->stack);
     pthread_mutex_unlock(&task_manager->lock);
     return task;
   }


   pthread_mutex_unlock(&task_manager->lock);
   //return NULL no task is given
   return NULL;
 }


 void UpdateWaitTime(TaskManager * task_manager){
   struct timeval    tp;

   int rc =  gettimeofday(&tp, NULL);
   task_manager->wait_to.tv_sec  = tp.tv_sec;
   task_manager->wait_to.tv_nsec = tp.tv_usec * 1000;
   task_manager->wait_to.tv_sec += TASK_WAIT_TIME;
   return;
 }

 int TPpthread_condattr_setclock (pthread_condattr_t *attr, clockid_t clock_id)
 {
   /* Only a few clocks are allowed.  */
   if (clock_id != 1 && clock_id != 0)
     /* If more clocks are allowed some day the storing of the clock ID
        in the pthread_cond_t structure needs to be adjusted.  */
     return 22;
   /* If we do not support waiting using CLOCK_MONOTONIC, return an error.  */
   if (clock_id == 1
       && !true)
     return ENOTSUP;
   /* Make sure the value fits in the bits we reserved.  */
   int *valuep = &((struct pthread_condattr *) attr)->value;
   *valuep = ((*valuep & ~(((1 << 1) - 1) << 1))
              | (clock_id << 1));
   return 0;
 }

 /*
   blocking pop waits until there is any task in the Stack
   when new task is added it safely removes and returns new task
   to be processed by thread from thread pool
 */
 void Dispose(TaskManager * task_manager) {

   //just sleep pop operation until there is any task in the stack
   pthread_mutex_lock(&task_manager->lock);

   FOR(k,0,task_manager->stack->size) {
     Task * task = StackPop(task_manager->stack);
     if (task->mode == DETACH) free(task);
   }

   FOR(k,0,task_manager->heap->size) {
     Task * task = (Task *)pop(task_manager->heap);
     if (task->mode == DETACH) free(task);
   }

   pthread_mutex_unlock(&task_manager->lock);

   //free internal stack data structure
   FreeStack(task_manager->stack);
   free(task_manager->stack);

   //free internal heap data strcuture
   FreeHeap(task_manager->heap);
   free(task_manager->heap);

   return;
 }
