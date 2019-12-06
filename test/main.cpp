#include <stdio.h>
#include <signal.h>


#include "../ThreadPool.h"


ThreadPool * tp;

void intHandler(int dummy) {
printf("interrupter = %d\n", pthread_self());
  ThreadPoolInterrupt(tp); return; }

void * calculate(void * val) {

  printf("%s\n","calculation started");
  int x = 0;
  FOR(k,0,1000000000) {
    x++;
  }

  printf("%d\n",x);
  return  NULL;
}

void * bla(void *) {
  int z = 0;
  FOR(k,0,10) {
    Task * task = NewTask(calculate,&z,TASK_MODE::DETACH);
    PushTask(tp,task);

  }
  return NULL;
}

int main() {
  printf("In function \nthread id = %d\n", pthread_self());
   // printf() displays the string inside quotation
   signal(SIGINT, intHandler);

   //create and start thread pool
   tp = ThreadPoolNew(4);
   ThreadPoolStart(tp);

   //create task feeding thread
   pthread_t thread;
   pthread_create(&thread,NULL,bla,NULL);
   ThreadPoolJoin(tp);
   ThreadPoolDispose(tp);

   return 0;
}
