typedef struct btnode *BTNode;
typedef BTNode QueueItemType;
typedef struct qNode{
   QueueItemType value;
   struct qNode *Link;
}queueNode;

typedef queueNode *queueNodePtr;

typedef struct q{
   queueNodePtr rear;
   queueNodePtr front;
}queue;

typedef queue *queueptr;
