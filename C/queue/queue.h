#include "queueTypes.h"
queueptr createQ();
void enqueue(queueptr q, QueueItemType item);
void dequeue(queueptr q, QueueItemType *item);
int empty(queueptr q);
