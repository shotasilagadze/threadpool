/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   PriorityQueue.h
 * Author: shotasilagadze
 *
 * Created on December 6, 2019, 2:50 PM
 */

#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H


#include <stdio.h>
#include <stdlib.h>



#ifdef __cplusplus
extern "C" {
#endif


typedef struct {
    int priority;
    char *data;
} node_t;

typedef struct {
    node_t *nodes;
    int len;
    int size;
} heap_t;


//Push new data item into heap
void push (heap_t *h, int priority, char *data);


//pop returns data * from heap
char *pop (heap_t *h);



#ifdef __cplusplus
}
#endif

#endif /* PRIORITYQUEUE_H */
