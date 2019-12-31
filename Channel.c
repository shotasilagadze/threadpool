/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

 #include "Channel.h"


Channel * CreateChannel() {
  //initialize starting values for channel
  Channel * channel = (Channel *)malloc(sizeof(Channel));
  channel->log_length = STARTING_LOG_LENGTH;
  channel->items = malloc(channel->log_length * sizeof(void *));
  channel->size = 0;

  pthread_mutex_init(&channel->lock,NULL);
  pthread_cond_init(&channel->cond_var,NULL);
  return channel;
}

void UpdateChannelWaitTime(Channel * channel){
  struct timeval    tp;

  int rc =  gettimeofday(&tp, NULL);
  channel->wait_to.tv_sec  = tp.tv_sec;
  channel->wait_to.tv_nsec = tp.tv_usec * 1000;
  channel->wait_to.tv_sec += CHANNEL_WAIT_TIME;
  return;
}


void ChannelPush(Channel * channel, void * item) {

  pthread_mutex_lock(&channel->lock);
  if (channel->log_length == channel->size) {
    channel->log_length *=2;
    channel->items = realloc(channel->items, channel->log_length * sizeof(void *));
  }

  channel->items[channel->size] = item;
  channel->size++;
  pthread_cond_signal(&channel->cond_var);
  pthread_mutex_unlock(&channel->lock);
}

void * ChannelPop(Channel * channel) {
  //loop while thread not interrupted
  while (channel->interrupt_requested != 1) {

    void * item = UnsafePop(channel);
    //process task if valid
    if (item != NULL) {
      return item;
    }
  }

  return NULL;
}

void * UnsafePop(Channel * channel) {
  pthread_mutex_lock(&channel->lock);

  //if item is available in channel just pop and return
  if (channel->size != 0) {
    void * item = channel->items[channel->size-1];
    channel->size--;
    pthread_mutex_unlock(&channel->lock);
    return item;
  }

  //cond var state check
  UpdateChannelWaitTime(channel);
  //just sleep pop operation until there is any task in the stack
  pthread_cond_timedwait(&channel->cond_var, &channel->lock, &channel->wait_to);

  if (channel->size != 0) {
    void * item = channel->items[channel->size-1];
    channel->size--;
    pthread_mutex_unlock(&channel->lock);
    return item;
  }

  pthread_mutex_unlock(&channel->lock);
  //return NULL no task is given
  return NULL;
}


//interrupt disposes stack (waking all other threads stuck in pop function)
void ChannelDispose(Channel * channel) {
  channel->interrupt_requested = 1;
  return;
}
