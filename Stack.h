/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Stack.h
 * Author: shotasilagadze
 *
 * Created on December 6, 2019, 4:15 PM
 */

#ifndef STACK_H
#define STACK_H

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

  //time to wait cond var to
  struct timespec wait_to;

} Stack;


//Push task to stack
void StackPush(Stack * stack, Task * task);

//pop task from stack
Task * StackPop(Stack * stack);

//assigns default parameters
void InitializeStack(Stack *stack);

//free stack data structure
void FreeStack(Stack * stack);

#ifdef __cplusplus
}
#endif

#endif /* STACK_H */
