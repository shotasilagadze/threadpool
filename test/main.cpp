#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>


#include "../ThreadPool.h"
#include "../Channel.h"

#define FOR(a,b,c) for(int a=b;a<c;a++)

ThreadPool * tp;
void intHandler(int dummy) {
  ThreadPoolInterrupt(tp);
  return;
}

void * SimpleCalculations(void * data) {
  printf("task - %lld  in progress\n",(long long)data);
  sleep(1);
  printf("task - %lld finished \n",(long long)data);
  return (void *)7;
}


void Test1() {
  tp = ThreadPoolNew(3);
  ThreadPoolStart(tp);
  long long i = 5;
  FOR(k,0,10) PushTask(tp,NewTask(SimpleCalculations,(void *)i,DETACH));

  ThreadPoolJoin(tp);
  ThreadPoolDispose(tp);
  printf("%s\n","Test 1: Success");

  return;
}

void * Starter(void *) {
  long long i = 5;
  FOR(k,0,10) PushTask(tp,NewTask(SimpleCalculations,(void *)i,DETACH));
  return NULL;
}

void Test3() {
  tp = ThreadPoolNew(3);
  ThreadPoolStart(tp);

  pthread_t thread;
  FOR(k,0,5) pthread_create(&thread, NULL, Starter, NULL);


  ThreadPoolJoin(tp);
  ThreadPoolDispose(tp);
  printf("%s\n","Test 3: Success");

  return;
}


void Test2() {
  tp = ThreadPoolNew(2);
  ThreadPoolStart(tp);

  long long i = 5;
  FOR(k,0,10) PushTask(tp,NewTask(SimpleCalculations,(void *)i,DETACH));

  ThreadPoolJoin(tp);
  ThreadPoolDispose(tp);
  printf("%s\n","Test 2: Success");

  return;
}

void Test4() {
  tp = ThreadPoolNew(2);
  ThreadPoolStart(tp);

  Task * task1 = NewTask(SimpleCalculations,(void *)1,WAIT);
  Task * task2 = NewTask(SimpleCalculations,(void *)2,WAIT);

  PushTask(tp,task1);
  PushTask(tp,task2);

  void * t1_res = GetResult(task1);
  void * t2_res = GetResult(task2);

  ThreadPoolJoin(tp);
  ThreadPoolDispose(tp);
  printf("%s\n","Test 4: Success");
  return;
}

void * ChannelPusher(void * channel) {
  int * bla = (int *)malloc(sizeof(int));
  *bla = 5;
  ChannelPush((Channel *)channel,(void *)bla);
  ChannelPush((Channel *)channel,(void *)bla);
  return NULL;

}


void Test5() {

  Channel * channel  = CreateChannel();
  FOR(k,0,5) {
    pthread_t thread;
    pthread_create(&thread, NULL, ChannelPusher, channel);
  }
  FOR(k,0,10) {
    void * item = ChannelPop(channel);
    printf("%d\n",*(int *)item);
  }

  printf("%s\n","Test 5: Success");
  return;
}





int main() {
   signal(SIGINT, intHandler);

   Test1();


   Test2();


   Test3();


   Test4();


   Test5();

   return 0;
}
