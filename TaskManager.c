/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "TaskManager.h"

 //The function wich will be with external linkage to thread pool for stack creation
 Stack * StackNew(int size) {
   Stack * sp = (Stack *)malloc(sizeof(Stack));
   sp->tasks = realloc(sp->tasks,size);
   sp->size = 0;
   sp->alloc_length = size*sizeof(void *);
   return sp;
 }

 //push just pushes new task into the queue increasing internal stack size if necessary
 void Push(Stack * stack, void * task)  {
   //make sure to push new task safely
   pthread_mutex_lock(&stack->lock);

   //make stack size twise as big to allocate enough space
   if (stack->alloc_length == stack->size) {
     stack->alloc_length*=2;
     stack->tasks = realloc(stack->tasks, stack->alloc_length*sizeof(void*));
   }

   //push task and increase size
   stack->tasks[stack->size] = task;
   stack->size++;

   //notify waiting thread that there is a new task to be processed
   pthread_cond_signal(&stack->cond_var);
   pthread_mutex_unlock(&stack->lock);
   return;
 }


 //(unsafe) push just pushes new task into the queue increasing internal stack size if necessary
 void * Pop(Stack * stack)  {
     if (stack->size == 0) return NULL;
     stack->size--;
     void * task_pt = stack->tasks[stack->size];

     return task_pt;
 }

 /*
   blocking pop waits until there is any task in the Stack
   when new task is added it safely removes and returns new task
   to be processed by thread from thread pool
 */
 void * BlockingPop(Stack * stack) {
   //just sleep pop operation until there is any task in the stack
   pthread_mutex_lock(&stack->lock);
   while (stack->size == 0) pthread_cond_wait(&stack->cond_var, &stack->lock);

   //when size > 0 remove task and return while unlocking lock
   stack->size--;
   void * task_pt = stack->tasks[stack->size];
   pthread_mutex_unlock(&stack->lock);

   //return task uniquely to one thread
   return task_pt;
 }
