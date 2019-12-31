/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Channel.h
 * Author: shota
 *
 * Created on December 31, 2019, 10:49 AM
 */

#ifndef CHANNEL_H
#define CHANNEL_H

#ifdef __cplusplus
extern "C" {
#endif


#include <pthread.h>
#include <stdlib.h>

#define STARTING_LOG_LENGTH 4
#define CHANNEL_WAIT_TIME 1

typedef struct Channel {

  //function which should process tasks
  void ** items;

  int log_length;

  int size;

  //thread safety parameters
  pthread_mutex_t lock;
  pthread_cond_t cond_var;

  //time to wait cond var to
  struct timespec wait_to;

  //boolean what shows if channel is interrupted
  int interrupt_requested;


} Channel;


//creating new channel
Channel * CreateChannel();

//blockingpop blocks until new item is available in channel
void * ChannelPop(Channel * channel);

//poping item from channel
void * UnsafePop(Channel * channel);

//safely pushing item and waking up waiting threads
void ChannelPush(Channel * channel, void * item);

//update waiting time
void UpdateChannelWaitTime(Channel * channel);





#ifdef __cplusplus
}
#endif

#endif /* CHANNEL_H */
