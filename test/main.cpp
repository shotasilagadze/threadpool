#include <stdio.h>
#include <signal.h>


#include "../ThreadPool.h"


ThreadPool * tp;

void intHandler(int dummy) {  ThreadPoolInterrupt(tp); return; }

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
    Task * task = NewTask(calculate,&z);
    PushTask(tp,task);

  }
  return NULL;
}

int main() {
  printf("In function \nthread id = %d\n", pthread_self());
   // printf() displays the string inside quotation
   signal(SIGINT, intHandler);

   //create and start thread pool
   tp = ThreadPoolNew(2);
   ThreadPoolStart(tp);

   //create task feeding thread
   pthread_t thread;
   pthread_create(&thread,NULL,bla,NULL);
   ThreadPoolJoin(tp);
   return 0;
}
