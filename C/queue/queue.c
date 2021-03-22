#include <stdio.h>
#include <stdlib.h>
#include "queueTypes.h"

queueptr createQ(){ //creates empty queue
	queueptr q = malloc(sizeof(queue));
   q->front = NULL;
   q->rear = NULL;
   return q;
}

int empty(queueptr q){ //if empty returns 1, if not empty returns 0, in case of uninitialized queue returns -1
   if(q == NULL) return -1;
   if(q->rear == NULL) return 1;
   return 0;
}

void enqueue(queueptr q, QueueItemType item){ //enqueues item to queue
   queueNodePtr new = malloc(sizeof(queueNode));
	new->Link = NULL;
   new->value = item;
   
   if(q == NULL){
		printf("Error: Queue not initialized.\n");	
	}else{
		if(q->front == NULL){
			q->front = new;
			q->rear = new;
		}else{
			q->rear->Link = new;
			q->rear = new;
		}
	}
}

void dequeue(queueptr q, QueueItemType *item){ //dequeues item
	if(q == NULL){
		printf("Error: Queue not initialized.\n");
	}else{
		if(empty(q)){
			printf("Error: Queue is empty.\n");
		}else{
			*item = q->front->value;
         queueNodePtr temp = q->front;
         q->front = q->front->Link; 
         free(temp);
			if(q->front == NULL) q->rear = NULL;
		}
	}
}
