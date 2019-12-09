/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

 #include "Stack.h"


void InitializeStack(Stack * stack) {
  //allocated memory length (bytes)
  stack->alloc_length = DEFAULT_STACK_ALLOCATION*sizeof(Task *);
  stack->tasks = malloc(stack->alloc_length);

  //initialy empty stack size
  stack->size = 0;
  return;
}

void StackPush(Stack * stack, Task * task) {
  //make stack size twise as big to allocate enough space
  if (stack->alloc_length == stack->size) {
   stack->alloc_length*=2;
   stack->tasks = realloc(stack->tasks, stack->alloc_length*sizeof(void*));
  }

  //push task and increase size
  stack->tasks[stack->size] = task;
  stack->size++;

  return;
}


Task * StackPop(Stack * stack) {
  if (stack->size == 0) {
    return NULL;
  }

  //when size > 0 remove task and return while unlocking lock
  stack->size--;
  void * task_pt = stack->tasks[stack->size];

  return task_pt;
}

void FreeStack(Stack * stack) {
  free(stack->tasks);
}
