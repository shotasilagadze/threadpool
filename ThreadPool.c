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
  tp->stack = StackNew(STACK_DEFAULT_SIZE);

  return tp;
}


void ThreadPoolStart(ThreadPool * tp) {

}
